#include <stdio.h>

static const char              IDBLOCK_01__FileIdentifier[8]                  = "MDF     ";
static const char              IDBLOCK_02__FormatIdentifier[8]                = "3.30    ";
static const char              IDBLOCK_03__ProgramIdentifier[8]               = "CUNIT2.3";
static const unsigned short    IDBLOCK_04__DefaultByteOrder                   = 0u;     /* Little Endian */
static const unsigned short    IDBLOCK_05__DefaultFloatingPointFormat         = 0u;     /* Compliant with IEEE 754 standard */
static const unsigned short    IDBLOCK_06__VersionNumber                      = 330u;   /* Version Number corresponds to 3.3 */
static const unsigned short    IDBLOCK_07__CodePageNumber                     = 0u;     /* 0=<unknown> */
static const char              IDBLOCK_08__RESERVED[2]                        = "";     /* Reserved space in ID_BLOCK */
static const char              IDBLOCK_09__RESERVED[30]                       = "";     /* Reserved space in ID_BLOCK */

static const char              HDBLOCK_01__BlockTypeIdentifier[2]             = "HD";
static       unsigned short    HDBLOCK_02__BlockSize                          = 0x0000u;         /* Block size in Bytes */ /* DYNAMIC */
static       unsigned int      HDBLOCK_03__PtrFirstDGBLOCK                    = 0x00000000u;     /* Block size in Bytes */ /* DYNAMIC */
static       unsigned int      HDBLOCK_04__PtrMeasurementFileComment          = 0x00000000u;                               /* DYNAMIC */
static       unsigned int      HDBLOCK_05__PtrPRBLOCK                         = 0x00000000u;                               /* DYNAMIC */
static       unsigned short    HDBLOCK_06__NumberOfDGBLOCKs                   = 0x0001u;                                   /* DYNAMIC */
static const char              HDBLOCK_07__DateOfRecord[10]                   = "31:12:2010";
static const char              HDBLOCK_08__TimeOfRecord[8]                    = "23:59:59";
static const char              HDBLOCK_09__NameOfAuthor[32]                   = "Author's name";
static const char              HDBLOCK_10__Organization[32]                   = "Organization";
static const char              HDBLOCK_11__Project[32]                        = "Project";
static const char              HDBLOCK_12__MeasurementObject[32]              = "MeasurementObject";
static const unsigned int      HDBLOCK_13__TimeStampPartOne                   = 0x00000000u;
static const unsigned int      HDBLOCK_14__TimeStampPartTwo                   = 0x00000000u;
static const signed short      HDBLOCK_15__UTCtimeOffset                      = 0x0000;
static const unsigned short    HDBLOCK_16__TimeQualityClass                   = 0x0000u; /* local PC reference time */
static const char              HDBLOCK_17__TimerIdentification[32]            = "Local PC Reference Time";

static const char              DGBLOCK_01__BlockTypeIdentifier[2]             = "DG";
static const unsigned short    DGBLOCK_02__BlockSize                          = 28u;     /* Block size in Bytes */
static       unsigned int      DGBLOCK_03__PtrNextDGBLOCK                     = 0x00000000u;     /* Block size in Bytes */ /* DYNAMIC */
static       unsigned int      DGBLOCK_04__PtrFirstCGBLOCK                    = 0x00000000u;                               /* DYNAMIC */
static       unsigned int      DGBLOCK_05__PtrTRBLOCK                         = 0x00000000u;                               /* DYNAMIC */
static       unsigned int      DGBLOCK_06__PtrDATA                            = 0x00000000u;                               /* DYNAMIC */
static       unsigned short    DGBLOCK_07__NumberOfCGBLOCKs                   = 0x0001u;
static       unsigned short    DGBLOCK_08__NumberOfRecordIDs                  = 0x0000u; /* data records without record ID */
static const unsigned int      DGBLOCK_09__Reserved                           = 0x00000000u;

static size_t count = 0;

FILE *mdf_open(const char *filename);

static void set_Infos(void){
#if 0
    time_t now;
    struct tm *ts;

    now = time(0);
    ts = localtime(&now);

    stftime(HDBLOCK_06__DateOfRecord, sizeof(HDBLOCK_06__DateOfRecord), "%d:%m:%Y", ts);
    stftime(HDBLOCK_07__TimeOfRecord, sizeof(HDBLOCK_07__TimeOfRecord), "%H:%M:%S", ts);
#endif /* 0 */
} /* set_Infos */


static void write__IDBLOCK(FILE *fp, size_t *count){
    *count += fwrite( IDBLOCK_01__FileIdentifier,                       1,                                              sizeof(IDBLOCK_01__FileIdentifier), fp);
    *count += fwrite( IDBLOCK_02__FormatIdentifier,                     1,                                              sizeof(IDBLOCK_02__FormatIdentifier), fp);
    *count += fwrite( IDBLOCK_03__ProgramIdentifier,                    1,                                              sizeof(IDBLOCK_03__ProgramIdentifier), fp);
    *count += fwrite(&IDBLOCK_04__DefaultByteOrder,                     sizeof(IDBLOCK_04__DefaultByteOrder),           1, fp);
    *count += fwrite(&IDBLOCK_05__DefaultFloatingPointFormat,           sizeof(IDBLOCK_05__DefaultFloatingPointFormat), 1, fp);
    *count += fwrite(&IDBLOCK_06__VersionNumber,                        sizeof(IDBLOCK_06__VersionNumber),              1, fp);
    *count += fwrite(&IDBLOCK_07__CodePageNumber,                       sizeof(IDBLOCK_07__CodePageNumber),             1, fp);
    *count += fwrite( IDBLOCK_08__RESERVED,                             1,                                              sizeof(IDBLOCK_08__RESERVED), fp);
    *count += fwrite( IDBLOCK_09__RESERVED,                             1,                                              sizeof(IDBLOCK_09__RESERVED), fp);
} /* write__ID_BLOCK */

static void write__HDBLOCK(FILE *fp, size_t *count){

    HDBLOCK_02__BlockSize =     sizeof(HDBLOCK_01__BlockTypeIdentifier)
                            +   sizeof(HDBLOCK_02__BlockSize)
                            +   sizeof(HDBLOCK_03__PtrFirstDGBLOCK)
                            +   sizeof(HDBLOCK_04__PtrMeasurementFileComment)
                            +   sizeof(HDBLOCK_05__PtrPRBLOCK)
                            +   sizeof(HDBLOCK_06__NumberOfDGBLOCKs)
                            +   sizeof(HDBLOCK_07__DateOfRecord)
                            +   sizeof(HDBLOCK_08__TimeOfRecord)
                            +   sizeof(HDBLOCK_09__NameOfAuthor)
                            +   sizeof(HDBLOCK_10__Organization)
                            +   sizeof(HDBLOCK_11__Project)
                            +   sizeof(HDBLOCK_12__MeasurementObject)
                            +   sizeof(HDBLOCK_13__TimeStampPartOne)
                            +   sizeof(HDBLOCK_14__TimeStampPartTwo)
                            +   sizeof(HDBLOCK_15__UTCtimeOffset)
                            +   sizeof(HDBLOCK_16__TimeQualityClass)
                            +   sizeof(HDBLOCK_17__TimerIdentification);

    HDBLOCK_03__PtrFirstDGBLOCK = *count + HDBLOCK_02__BlockSize + 4; /* TODO: Remove this 4. Where does it come from?? */

    *count += fwrite( HDBLOCK_01__BlockTypeIdentifier,                  1,                                              sizeof(HDBLOCK_01__BlockTypeIdentifier), fp);
    *count += fwrite(&HDBLOCK_02__BlockSize,                            sizeof(HDBLOCK_02__BlockSize),                  1, fp);
    *count += fwrite(&HDBLOCK_03__PtrFirstDGBLOCK,                      sizeof(HDBLOCK_03__PtrFirstDGBLOCK),            1, fp);
    *count += fwrite(&HDBLOCK_04__PtrMeasurementFileComment,            sizeof(HDBLOCK_04__PtrMeasurementFileComment),  1, fp);
    *count += fwrite(&HDBLOCK_05__PtrPRBLOCK,                           sizeof(HDBLOCK_05__PtrPRBLOCK),                 1, fp);
    *count += fwrite(&HDBLOCK_06__NumberOfDGBLOCKs,                     sizeof(HDBLOCK_06__NumberOfDGBLOCKs),           1, fp);
    *count += fwrite( HDBLOCK_07__DateOfRecord,                         1,                                              sizeof(HDBLOCK_07__DateOfRecord), fp);
    *count += fwrite( HDBLOCK_08__TimeOfRecord,                         1,                                              sizeof(HDBLOCK_08__TimeOfRecord), fp);
    *count += fwrite( HDBLOCK_09__NameOfAuthor,                         1,                                              sizeof(HDBLOCK_09__NameOfAuthor), fp);
    *count += fwrite( HDBLOCK_10__Organization,                         1,                                              sizeof(HDBLOCK_10__Organization), fp);
    *count += fwrite( HDBLOCK_11__Project,                              1,                                              sizeof(HDBLOCK_11__Project), fp);
    *count += fwrite( HDBLOCK_12__MeasurementObject,                    1,                                              sizeof(HDBLOCK_12__MeasurementObject), fp);
    *count += fwrite(&HDBLOCK_13__TimeStampPartOne,                     sizeof(HDBLOCK_13__TimeStampPartOne),           1, fp);
    *count += fwrite(&HDBLOCK_14__TimeStampPartTwo,                     sizeof(HDBLOCK_14__TimeStampPartTwo),           1, fp);
    *count += fwrite(&HDBLOCK_15__UTCtimeOffset,                        sizeof(HDBLOCK_15__UTCtimeOffset),              1, fp);
    *count += fwrite(&HDBLOCK_16__TimeQualityClass,                     sizeof(HDBLOCK_16__TimeQualityClass),           1, fp);
    *count += fwrite( HDBLOCK_17__TimerIdentification,                  1,                                              sizeof(HDBLOCK_17__TimerIdentification), fp);
} /* write__HDBLOCK */

static void write__DGBLOCK(FILE *fp, size_t *count){

    *count += fwrite( DGBLOCK_01__BlockTypeIdentifier,                  1,                                              sizeof(DGBLOCK_01__BlockTypeIdentifier), fp);
    *count += fwrite(&DGBLOCK_02__BlockSize,                            sizeof(DGBLOCK_02__BlockSize),                  1, fp);
    *count += fwrite(&DGBLOCK_03__PtrNextDGBLOCK,                       sizeof(DGBLOCK_03__PtrNextDGBLOCK),             1, fp);
    *count += fwrite(&DGBLOCK_04__PtrFirstCGBLOCK,                      sizeof(DGBLOCK_04__PtrFirstCGBLOCK),            1, fp);
    *count += fwrite(&DGBLOCK_05__PtrTRBLOCK,                           sizeof(DGBLOCK_05__PtrTRBLOCK),                 1, fp);
    *count += fwrite(&DGBLOCK_06__PtrDATA,                              sizeof(DGBLOCK_06__PtrDATA),                    1, fp);
    *count += fwrite(&DGBLOCK_07__NumberOfCGBLOCKs,                     sizeof(DGBLOCK_07__NumberOfCGBLOCKs),           1, fp);
    *count += fwrite(&DGBLOCK_08__NumberOfRecordIDs,                    sizeof(DGBLOCK_08__NumberOfRecordIDs),          1, fp);
    *count += fwrite(&DGBLOCK_09__Reserved,                             sizeof(DGBLOCK_09__Reserved),                   1, fp);
} /* write__DGBLOCK */

FILE *mdf_open(const char *filename)
{
   FILE *fp = NULL;
   fp = fopen(filename, "wb");
   if(NULL == fp)
   {
      return fp;
   }

   set_Infos();
   write__IDBLOCK(fp, &count);
   write__HDBLOCK(fp, &count);
   write__DGBLOCK(fp, &count);

   return fp;
}
