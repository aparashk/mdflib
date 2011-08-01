enum VarIOType {
  VARP_EMPTY,
  VARP_INPUT,
  VARP_OUTPUT,
  VARP_INPUT_OUTPUT,
};

enum ValType {
  VAL_EMPTY,
  VAL_DOUBLE,
  VAL_DOUBLE_PTR,
  VAL_FLOAT,
  VAL_FLOAT_PTR,
  VAL_sLONG,
  VAL_sLONG_PTR,
  VAL_uLONG,
  VAL_uLONG_PTR,
  VAL_sSHORT,
  VAL_sSHORT_PTR,
  VAL_uSHORT,
  VAL_uSHORT_PTR,
  VAL_sCHAR,
  VAL_sCHAR_PTR,
  VAL_uCHAR,
  VAL_uCHAR_PTR,
  VAL_STRING,
  VAL_STRING_PTR,
  VAL_CSTRING,
  VAL_CSTRING_PTR
};

#define  DEF_signed_char       VAL_sCHAR
#define  DEF_unsigned_char     VAL_uCHAR
#define  DEF_signed_int        VAL_sLONG
#define  DEF_unsigned_int      VAL_uLONG
#define  DEF_signed_long       VAL_sLONG
#define  DEF_unsigned_long     VAL_uLONG
#define  DEF_float             VAL_FLOAT
#define  DEF_double            VAL_DOUBLE
#define  DEF_string            VAL_STRING
#define  DEF_unsigned_short    VAL_uSHORT
#define  DEF_signed_short      VAL_sSHORT

#define VAR_ARRAYEND {0}

#define MAX_VAL_STRING  128

struct SExtVariable {
  char*             str_ptr;      // name
  void*             val_ptr;      // address
  enum ValType      val_type;     // type
  enum VarIOType    var_prop_io;  // direction
  char*             group_ptr;    // group
  char*             unit_ptr;     // unit
  char*             comment_ptr;  // comment
  double            scale;        // scale
  double            offset;       // offset
  double            init;         // init
};

struct SExtVariableA {
  char*             str_ptr;      // name
  void*             val_ptr;      // address
  enum ValType      val_type;     // typ
  int               val_length;   // length
  enum VarIOType    var_prop_io;  // iO
  char*             group_ptr;    // group
  char*             unit_ptr;     // unit
  char*             comment_ptr;  // comment
  double            scale;        // scale
  double            offset;       // offset
  double            init;         // init
};

extern FILE *mdf_open(const char *filename, struct SExtVariable *table, struct SExtVariableA *tableA);
