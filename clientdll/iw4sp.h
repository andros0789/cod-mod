#pragma once

#define PROTOCOL 144
#define MASTER_SERVER "127.0.0.1"

typedef enum assetType_e
{
	ASSET_TYPE_PHYSPRESET = 0,
	ASSET_TYPE_PHYS_COLLMAP = 1,
	ASSET_TYPE_XANIM = 2,
	ASSET_TYPE_XMODELSURFS = 3,
	ASSET_TYPE_XMODEL = 4,
	ASSET_TYPE_MATERIAL = 5,
	ASSET_TYPE_PIXELSHADER = 6,
	ASSET_TYPE_VERTEXSHADER = 7,
	ASSET_TYPE_VERTEXDECL = 8,
	ASSET_TYPE_TECHSET = 9,
	ASSET_TYPE_IMAGE = 10,
	ASSET_TYPE_SOUND = 11,
	ASSET_TYPE_SNDCURVE = 12,
	ASSET_TYPE_LOADED_SOUND = 13,
	ASSET_TYPE_COL_MAP_SP = 14,
	ASSET_TYPE_COL_MAP_MP = 15,
	ASSET_TYPE_COM_MAP = 16,
	ASSET_TYPE_GAME_MAP_SP = 17,
	ASSET_TYPE_GAME_MAP_MP = 18,
	ASSET_TYPE_MAP_ENTS = 19,
	ASSET_TYPE_FX_MAP = 20,
	ASSET_TYPE_GFX_MAP = 21,
	ASSET_TYPE_LIGHTDEF = 22,
	ASSET_TYPE_UI_MAP = 23,
	ASSET_TYPE_FONT = 24,
	ASSET_TYPE_MENUFILE = 25,
	ASSET_TYPE_MENU = 26,
	ASSET_TYPE_LOCALIZE = 27,
	ASSET_TYPE_WEAPON = 28,
	ASSET_TYPE_SNDDRIVERGLOBALS = 29,
	ASSET_TYPE_FX = 30,
	ASSET_TYPE_IMPACTFX = 31,
	ASSET_TYPE_AITYPE = 32,
	ASSET_TYPE_MPTYPE = 33,
	ASSET_TYPE_CHARACTER = 34,
	ASSET_TYPE_XMODELALIAS = 35,
	ASSET_TYPE_RAWFILE = 36,
	ASSET_TYPE_STRINGTABLE = 37,
	ASSET_TYPE_LEADERBOARDDEF = 38,
	ASSET_TYPE_STRUCTUREDDATADEF = 39,
	ASSET_TYPE_TRACER = 40,
	ASSET_TYPE_VEHICLE = 41,
	ASSET_TYPE_ADDON_MAP_ENTS = 42,
	ASSET_TYPE_MAX = 43
} assetType_t;

typedef enum
{
	DVAR_FLAG_NONE			= 0x0,			//no flags
	DVAR_FLAG_SAVED		    = 0x1,			//saves in config_mp.cfg for clients
	DVAR_FLAG_LATCHED		= 0x2,			//no changing apart from initial value (although it might apply on a map reload, I think)
	DVAR_FLAG_CHEAT			= 0x4,			//cheat
	DVAR_FLAG_REPLICATED	= 0x8,			//on change, this is sent to all clients (if you are host)
	DVAR_FLAG_UNKNOWN10		= 0x10,			//unknown
	DVAR_FLAG_UNKNOWN20		= 0x20,			//unknown
	DVAR_FLAG_UNKNOWN40		= 0x40,			//unknown
	DVAR_FLAG_SERVER		= 0x80,			//server dvar
	DVAR_FLAG_USERCREATED	= 0x100,		//a 'set' type command created it
	DVAR_FLAG_USERINFO		= 0x200,		//userinfo?
	DVAR_FLAG_SERVERINFO	= 0x400,		//in the getstatus oob
	DVAR_FLAG_WRITEPROTECTED= 0x800,		//write protected
	DVAR_FLAG_UNKNOWN1000	= 0x1000,		//unknown
	DVAR_FLAG_READONLY		= 0x2000,		//read only (same as 0x800?)
	DVAR_FLAG_UNKNOWN4000	= 0x4000,		//unknown
	DVAR_FLAG_UNKNOWN8000	= 0x8000,		//unknown
	DVAR_FLAG_UNKNOWN10000  = 0x10000,		//unknown
	DVAR_FLAG_DEDISAVED		= 0x1000000,		//unknown
	DVAR_FLAG_NONEXISTENT	= 0xFFFFFFFF	//no such dvar
} dvar_flag;

typedef enum
{
	DVAR_TYPE_BOOL		= 0,
	DVAR_TYPE_FLOAT		= 1,
	DVAR_TYPE_FLOAT_2	= 2,
	DVAR_TYPE_FLOAT_3	= 3,
	DVAR_TYPE_FLOAT_4	= 4,
	DVAR_TYPE_INT		= 5,
	DVAR_TYPE_ENUM		= 6,
	DVAR_TYPE_STRING	= 7,
	DVAR_TYPE_COLOR		= 8,
	//DVAR_TYPE_INT64	= 9 only in Tx
} dvar_type;
// 67/72 bytes figured out
union dvar_value_t {
		char*	string;
		int		integer;
		float	value;
		bool	boolean;
		float	vec2[2];
		float	vec3[3];
		float	vec4[4];
		BYTE	color[4]; //to get float: multiply by 0.003921568859368563 - BaberZz
		//__int64 integer64; only in Tx
};
union dvar_maxmin_t {
	int i;
	float f;
};
typedef struct dvar_t
{
	//startbyte:endbyte
	const char*		name; //0:3
	const char*		description; //4:7
	unsigned int	flags; //8:11
	char			type; //12:12
	char			pad2[3]; //13:15
	dvar_value_t	current; //16:31
	dvar_value_t	latched; //32:47
	dvar_value_t	default; //48:64
	dvar_maxmin_t min; //65:67
	dvar_maxmin_t max; //68:72 woooo
} dvar_t;

typedef struct dvar_MW3_t
{
	const char*		name;
	short			flags;
	char			pad1[2];
	char			type;
	char			pad2[3];
	dvar_value_t	current;
	dvar_value_t	latched;
	dvar_value_t	default;
	dvar_maxmin_t min;
	dvar_maxmin_t max;
} dvar_MW3_t;

typedef struct cmd_function_s
{
	char pad[24];
} cmd_function_t;

// material stuff
struct GfxImage
{
        char* texture;
        char unknown2;
        char a3;
        char a2;
        char unknown3;
        char unknown4;
        char unknown5;
        char unknown6;
        char a4;
        int dataLength1;
        int dataLength2;
        short height;
		short width;
        short depth;
        short unknown8;
        char* name;
};

struct MaterialTextureDef
{
	unsigned int typeHash; // asset hash of type
	char firstCharacter; // first character of image name
	char secondLastCharacter; // second-last character of image name (maybe only in CoD4?!)
	unsigned char unknown; // maybe 0xE2
	char unknown2; // likely 0x00
	GfxImage* image; // GfxImage* actually
};

struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DTexture9;
struct IDirect3DVertexDeclaration9;

struct VertexDecl
{
	const char* name;
	int unknown;
	char pad[28];
	IDirect3DVertexDeclaration9* declarations[16];
};

struct PixelShader
{
	const char* name;
	IDirect3DPixelShader9* shader;
	DWORD* bytecode;
	int flags;
};

struct VertexShader
{
	const char* name;
	IDirect3DVertexShader9* shader;
	DWORD* bytecode;
	int flags;
};

struct MaterialPass
{
	VertexDecl* vertexDecl;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	char pad[8];
};

struct MaterialTechnique
{
	int pad;
	short pad2;
	short numPasses;
	MaterialPass passes[1];
};

struct MaterialTechniqueSet
{
	const char* name;
	char pad[4];
	MaterialTechniqueSet* remappedTechniqueSet;
	MaterialTechnique* techniques[48];
};

struct Material
{
	const char* name;
	unsigned short flags; // 0x2F00 for instance
	unsigned char animationX; // amount of animation frames in X
	unsigned char animationY; // amount of animation frames in Y
	char unknown1[4]; // 0x00
	unsigned int rendererIndex; // only for 3D models
	char unknown9[4];
	unsigned int surfaceTypeBits;
	unsigned int unknown2; // 0xFFFFFFFF
	unsigned int unknown3; // 0xFFFFFF00
	char unknown4[40]; // 0xFF
	char numMaps; // 0x01, possibly 'map count' (zone code confirms)
	char unknown5; // 0x00
	char unknownCount2; // 0x01, maybe map count actually
	char unknown6; // 0x03
	unsigned int unknown7; // 0x04
	MaterialTechniqueSet* techniqueSet; // '2d' techset; +80
	MaterialTextureDef* maps; // map references
	unsigned int unknown8;
	void* stateMap; // might be NULL, need to test
};

struct XModelAngle
{
	short x;
	short y;
	short z;
	short base; // defines the 90-degree point for the shorts
};

struct XModelTagPos
{
	float x;
	float y;
	float z;
};

struct XSurface
{
	short pad;
	short numVertices;
	short numPrimitives;
	unsigned char streamHandle; // something to do with buffers
	char pad2;
	int pad3;
	void* indexBuffer;
	char pad4[12];
	void* vertexBuffer;
	char pad5[32];
};

struct XModelSurfs
{
	const char* name;
	XSurface* surfaces;
	int numSurfaces;
	char pad[24];
};

struct XSurfaceLod
{
	char pad[8];
	XModelSurfs* surfaces;
	char pad2[32];
};

struct XModel
{
	char* name; // +0
	char numBones; // +4
	char numSubBones;
	char numMaterials;
	char pad2;
	char pad3[28]; // +8
	short* boneNames; // +36
	char* boneUnknown1; // +40
	XModelAngle* tagAngles; // +44, element size 8
	XModelTagPos* tagPositions; // +48, element size 12
	char* boneUnknown4; // +52
	char* boneUnknown5; // +56, element size 32
	Material** materials; // +60
	XSurfaceLod lods[4];
	int pad4; // +240
	char* stuffs; // +244
	int numStuffs; // +248
	int pad6;
	void* unknowns; // bone count, +256, element size 28
	char pad5[36];
	void* physPreset;
	void* physCollmap;
}; // total size 304

// netadr_t
typedef enum {
	NA_BOT,
	NA_BAD,					// an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	//NA_IP6,
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef enum {
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

typedef struct {
	netadrtype_t	type;

	BYTE	ip[4];

	unsigned short	port;

	BYTE	ipx[10];
} netadr_t;


/*#pragma pack(push, 1)
typedef struct
{
	netadrtype_t type;

	union
	{
		BYTE ip[4];
		BYTE ip6[16];
	};

	unsigned short port;
} netadr_t;
#pragma pack(pop)*/

typedef struct  
{
	int unknown1;
	int unknown2;
	char* data;
	int unknown3;
	int maxsize; // 16
	int cursize;
	int unknown4;
	int readcount; // 28
} msg_t;

typedef struct  
{
	int curClients;
	int maxClients;
	char map[128];
} svstatus_t;

struct XZoneInfo {
	const char* name;
	int type1;
	int type2;
};

typedef struct fontEntry_s
{
	unsigned short character;
	unsigned char padLeft;
	unsigned char padTop;
	unsigned char padRight;
	unsigned char width;
	unsigned char height;
	unsigned char const0;
	float uvLeft;
	float uvTop;
	float uvRight;
	float uvBottom;
} fontEntry_t;

typedef struct Font_s
{
	char* name;
	int size;
	int entries;
	Material* image;
	Material* glowImage;
	fontEntry_t* characters;
} Font;

typedef float vec4_t[4];

/*typedef struct
{
	float x;
	float y;
	float w;
	float h;
} rectangleDef_t;

typedef rectangleDef_t Rectangle;*/

typedef struct  
{
	int type;
	int id;
	void* extraData;
} menuExpToken_t;

typedef struct  
{
	int count;
	menuExpToken_t* tokens;
} menuExpression_t;

typedef struct  
{
	void* data;
	int type;
} menuStatement_t;

typedef struct  
{
	int numStatements;
	menuStatement_t** statements;
} menuScript_t;

typedef struct
{
	char* name;
	vec4_t rect;
	char rectAlignX;
	char rectAlignY;
	// 22
	char pad[2];
	// 24
	float originX;
	float originY;
	// 32
	char pad2[12];
	// 44
	char* group;
	// 48
	int style;
	int border;
	int ownerDraw;
	int ownerDrawFlags;
	float borderSize;
	// 68
	int flags1;
	int flags2;
	int unknown1;
	// 80
	vec4_t foreColor;
	vec4_t backColor;
	vec4_t borderColor;
	vec4_t outlineColor;
	// 144
	vec4_t unknownColor;
	// 160
	Material* background;
} windowDef_t;

typedef windowDef_t Window;

#define MAX_LB_COLUMNS 16

typedef struct columnInfo_s {
	int pos;
	int width;
	int maxChars;
	int unknown;
} columnInfo_t;

typedef struct listBoxDef_s {
	int cursorPos;
	int unk;
	int startPos;
	int endPos;
	float elementWidth;
	float elementHeight;
	int elementStyle;
	int numColumns;
	columnInfo_t columnInfo[MAX_LB_COLUMNS];
	menuScript_t* doubleClick;
	int notselectable;
	int noscrollbars;
	int usepaging;
} listBoxDef_t;

typedef struct  
{
	int type;
	menuExpression_t* expression;
} componentExpression_t;

typedef struct
{
	int expression;
	char* comp1;
	char* comp2;
} componentExpressionDef_t;

extern componentExpressionDef_t* componentExpressions;

typedef struct execKey_s
{
	union
	{
		char key[4];
		int keyInt;
	};
	menuScript_t* script;
	execKey_s* next;
} execKey_t;

typedef struct  
{
	Window window;
	// 164
	char pad1[20];
	// 184
	int type;
	int unknownType;
	int align;
	int textFont;
	int textAlign;
	float textAlignX;
	float textAlignY;
	float textScale;
	int textStyle;
	int unknown;
	int unknown2;
	char* text;
	int unknown3;
	int unknown4;
	menuScript_t* mouseEnterText;
	menuScript_t* mouseExitText;
	menuScript_t* mouseEnter;
	menuScript_t* mouseExit;
	menuScript_t* action;
	menuScript_t* accept;
	menuScript_t* onFocus;
	menuScript_t* leaveFocus;
	char* dvar;
	char* dvarTest;
	execKey_t* execKeys;
	void* testDvarValue;
	char* localVar;
	int testDvarType;
	char** focusSound;
	float feeder;
	int cursorPos;
	void* typeData;
	char pad2[4];
	int numExpressions;
	componentExpression_t* expressions;
	menuExpression_t* visibleExp;
	menuExpression_t* disabledExp;
	menuExpression_t* textExp;
	menuExpression_t* materialExp;
} itemDef_t;

typedef struct
{
	Window window;
	int unknown2;
	int fullscreen;
	int numItems;
	int unknown3;
	int unknown4;
	int fadeCycle;
	float fadeClamp;
	float fadeAmount;
	float fadeInAmount;
	float blurWorld;
	menuScript_t* onOpen;
	menuScript_t* onRequestClose;
	menuScript_t* onClose;
	menuScript_t* onESC;
	execKey_t* execKeys;
	void* visibleExp;
	char* allowedBinding;
	char* soundLoop;
	int unknown5;
	vec4_t focusColor;
	void* rectXExp;
	void* rectYExp;
	void* rectHExp;
	void* rectWExp;
	void* openSoundExp;
	void* closeSoundExp;
	itemDef_t** items;
} menuDef_t;

struct RawFile
{
	char* name;
	int compressedSize; // no trailing \0 in the string
	int size; // excludes the trailing \0
	char* data;
};

typedef struct  
{
	char type;
	char pad[3];
	const char** folder;
	const char* file;
} StreamFile;

typedef struct  
{
	char pad[20];
	StreamFile* stream;
	char pad2[76];
} snd_alias_t;

typedef struct  
{
	const char* name;
	snd_alias_t* aliases;
	int numAliases;
} snd_alias_list_t;

typedef struct
{
	char			pakFilename[256];			// c:\quake3\baseq3\pak0.pk3
	char			pakBasename[256];			// pak0
	char			pakGamename[256];			// baseq3
	int				handle;						// handle to zip file
	int				checksum;
} pack_t;

typedef struct {
	char		path[256];		// c:\quake3
	char		gamedir[256];	// baseq3
} directory_t;

typedef struct searchpath_s
{
	searchpath_s* next;
	pack_t* pack;
	directory_t* dir;
} searchpath_t;

typedef struct gclient_s {
	unsigned char pad[12764];
	unsigned int team;
	char pad2[1164];
} gclient_t;

typedef struct  
{
	int trType;
	int trTime;
	int trDuration;
	float trBase[3];
	float trDelta[3];
} trajectory_t;

typedef struct  
{
	int entityNum; // 0
	int eType; // 4
	char pad[4]; // 8
	trajectory_t pos; // 12
	trajectory_t apos; // 48
	char pad2[60]; // 84
	int itemIndex; // 144 (actually index.item)
	char pad3[16];
	int eventParm; // 164
	int pad4; // 168
	int events[4]; // 172
	int eventParms[4]; // 188
	char pad5[12]; // 204
	int un1; // 216
} entityState_t;
	
typedef struct gentity_s {
	unsigned char pad[312]; // 0
	float origin[3]; // 312
	float angles[3]; // 324
	char pad2[8];
	gclient_t* client; // 344
	unsigned char pad3[28];
	short classname;
	short pad4;
	unsigned char pad5[248];
} gentity_t;

#pragma pack(push, 1)
typedef struct client_s
{
	// 0
	int state;
	// 4
	char pad[36];
	// 40
	netadr_t adr;
	// 60
	char pad1[1568];
	// 1628
	char connectInfoString[1024];
	// 2652
	char pad2[133192];
	// 135844
	char name[16];
	// 135860
	char pad3[12];
	// 135872
	int snapNum;
	// 135876
	int pad4;
	// 135880
	short ping;
	// 135882
	//char pad5[142390];
	char pad5[133158];
	// 269040
	int isBot;
	// 269044
	char pad6[9228];
	// 278272
	__int64 steamid;
	// 278280
	char pad7[403592];
} client_t;
#pragma pack(pop)

enum scriptType_e
{
	SCRIPT_NONE = 0,
	SCRIPT_OBJECT = 1,
	SCRIPT_STRING = 2,
	SCRIPT_VECTOR = 4,
	SCRIPT_FLOAT = 5,
	SCRIPT_INTEGER = 6
};

typedef struct  
{
	union
	{
		void* entity;
		float number;
		unsigned short string;
		float* vector;
		int integer;
	};
	scriptType_e type;
} VariableValue;

typedef enum
{
	STRUCTURED_DATA_INT = 0,
	STRUCTURED_DATA_BYTE = 1,
	STRUCTURED_DATA_BOOL = 2,
	STRUCTURED_DATA_STRING = 3,
	STRUCTURED_DATA_ENUM = 4,
	STRUCTURED_DATA_STRUCT = 5,
	STRUCTURED_DATA_INDEXEDARR = 6,
	STRUCTURED_DATA_ENUMARR = 7,
	STRUCTURED_DATA_FLOAT = 8,
	STRUCTURED_DATA_SHORT = 9
} structuredDataType_t;

typedef struct
{
	structuredDataType_t type;
	union
	{
		int index;
	};
	int offset;
} structuredDataItem_t;

typedef struct
{
	const char* name;
	structuredDataItem_t item;
} structuredDataChild_t;

typedef struct
{
	int numChildren;
	structuredDataChild_t* children;
	int unknown1;
	int unknown2;
} structuredDataStruct_t;

typedef struct
{
	int enumIndex;
	structuredDataItem_t item;
} structuredDataEnumArray_t;

typedef struct
{
	const char* key;
	int index;
} structuredDataEnumIndex_t;

typedef struct
{
	int numIndices;
	int unknown;
	structuredDataEnumIndex_t* indices;
} structuredDataEnum_t;

typedef struct
{
	int numItems;
	structuredDataItem_t item;
} structuredDataIndexedArray_t;

typedef struct
{
	int version;
	unsigned int hash;
	int numEnums;
	structuredDataEnum_t* enums;
	int numStructs;
	structuredDataStruct_t* structs;
	int numIndexedArrays;
	structuredDataIndexedArray_t* indexedArrays;
	int numEnumArrays;
	structuredDataEnumArray_t* enumArrays;
	structuredDataItem_t rootItem;
} structuredData_t;

typedef struct
{
	const char* name;
	int unknown;
	structuredData_t* data;
} structuredDataDef_t;

typedef struct
{
	structuredData_t* data;
	structuredDataItem_t* item;
	int offset;
	int error;
} structuredDataFindState_t;

struct localizedEntry_s
{
	const char* value;
	const char* name;
};

#define FS_SEEK_CUR 0
#define FS_SEEK_END 1
#define FS_SEEK_SET 2

// inline cmd functions
extern DWORD* cmd_id;
extern DWORD* cmd_argc;
extern DWORD** cmd_argv;

inline int	Cmd_Argc( void )
{
	return cmd_argc[*cmd_id];
}

inline char *Cmd_Argv( int arg )
{
	if ( (unsigned)arg >= cmd_argc[*cmd_id] ) {
		return "";
	}
	return (char*)(cmd_argv[*cmd_id][arg]);	
}

char* GetStringConvar(char* key);

GfxImage* Image_Load(const char* name);

// Menu stuff
typedef struct  
{
	char* filename;
	int count;
	menuDef_t** menuFiles;
} menuFile_t;

// Q3TA precompiler code

//undef if binary numbers of the form 0b... or 0B... are not allowed
#define BINARYNUMBERS
//undef if not using the token.intvalue and token.floatvalue
#define NUMBERVALUE
//use dollar sign also as punctuation
#define DOLLAR

//maximum token length
#define MAX_TOKEN					1024

//punctuation
typedef struct punctuation_s
{
	char *p;						//punctuation character(s)
	int n;							//punctuation indication
	struct punctuation_s *next;		//next punctuation
} punctuation_t;

//token
typedef struct token_s
{
	char string[MAX_TOKEN];			//available token
	int type;						//last read token type
	int subtype;					//last read token sub type
#ifdef NUMBERVALUE
	unsigned long int intvalue;	//integer value
	long double floatvalue;			//floating point value
#endif //NUMBERVALUE
	char *whitespace_p;				//start of white space before token
	char *endwhitespace_p;			//start of white space before token
	int line;						//line the token was on
	int linescrossed;				//lines crossed in white space
	struct token_s *next;			//next token in chain
} token_t;

//script file
typedef struct script_s
{
	char filename[64];				//file name of the script
	char *buffer;					//buffer containing the script
	char *script_p;					//current pointer in the script
	char *end_p;					//pointer to the end of the script
	char *lastscript_p;				//script pointer before reading token
	char *whitespace_p;				//begin of the white space
	char *endwhitespace_p;			//end of the white space
	int length;						//length of the script in bytes
	int line;						//current line in script
	int lastline;					//line before reading token
	int tokenavailable;				//set by UnreadLastToken
	int flags;						//several script flags
	punctuation_t *punctuations;	//the punctuations used in the script
	punctuation_t **punctuationtable;
	token_t token;					//available token
	struct script_s *next;			//next script in a chain
} script_t;

//macro definitions
typedef struct define_s
{
	char *name;							//define name
	int flags;							//define flags
	int builtin;						// > 0 if builtin define
	int numparms;						//number of define parameters
	token_t *parms;						//define parameters
	token_t *tokens;					//macro tokens (possibly containing parm tokens)
	struct define_s *next;				//next defined macro in a list
	struct define_s *hashnext;			//next define in the hash chain
} define_t;

//indents
//used for conditional compilation directives:
//#if, #else, #elif, #ifdef, #ifndef
typedef struct indent_s
{
	int type;								//indent type
	int skip;								//true if skipping current indent
	script_t *script;						//script the indent was in
	struct indent_s *next;					//next indent on the indent stack
} indent_t;

//source file
typedef struct source_s
{
	char filename[64];					//file name of the script
	char includepath[64];					//path to include files
	punctuation_t *punctuations;			//punctuations to use
	script_t *scriptstack;					//stack with scripts of the source
	token_t *tokens;						//tokens to read first
	define_t *defines;						//list with macro definitions
	define_t **definehash;					//hash chain with defines
	indent_t *indentstack;					//stack with indents
	int skip;								// > 0 if skipping conditional code
	token_t token;							//last read token
} source_t;

#define MAX_TOKENLENGTH		1024

typedef struct pc_token_s
{
	int type;
	int subtype;
	int intvalue;
	float floatvalue;
	char string[MAX_TOKENLENGTH];
} pc_token_t;

//token types
#define TT_STRING						1			// string
#define TT_LITERAL					2			// literal
#define TT_NUMBER						3			// number
#define TT_NAME						4			// name
#define TT_PUNCTUATION				5			// punctuation

//typedef int menuDef_t;
//typedef int itemDef_t;

#define KEYWORDHASH_SIZE	512

typedef struct keywordHash_s
{
	char *keyword;
	bool (*func)(itemDef_t *item, int handle);
	//struct keywordHash_s *next;
} keywordHash_t;

typedef int scr_entref_t;
typedef void (__cdecl * scr_function_t)(scr_entref_t);

typedef struct  
{
	const char* functionName;
	scr_function_t functionCall;
	int developerOnly;
} scr_funcdef_t;

struct script_functiondef
{
	int id;
	void (*func)(int);
	int unknown;
};

enum errorParm_s
{
	ERR_FATAL,                  // exit the entire game with a popup window
	ERR_DROP,                   // print to console and disconnect from game
	ERR_SERVERDISCONNECT,       // don't kill server
	ERR_DISCONNECT,             // client disconnected from the server
	ERR_NEED_CD                 // pop up the need-cd dialog
};

static void nullfunc(int){}

// types
typedef void (__cdecl * CommandCB_t)(void);

extern "C"
{
// original functions
typedef void* (__cdecl * BG_LoadWeaponDef_LoadObj_t)(const char* filename);
extern BG_LoadWeaponDef_LoadObj_t BG_LoadWeaponDef_LoadObj;
	

typedef void (__cdecl * Cbuf_AddText_t)(int a1, const char* cmd);
extern Cbuf_AddText_t Cbuf_AddText;


typedef void (__cdecl * CL_AddReliableCommand_t)(int controller, const char* command);
extern CL_AddReliableCommand_t CL_AddReliableCommand;

typedef int (__cdecl * CL_IsCgameInitialized_t)();
extern CL_IsCgameInitialized_t CL_IsCgameInitialized;


typedef void (__cdecl * Cmd_AddCommand_t)(const char* name, CommandCB_t callback, cmd_function_t* data, char);
extern Cmd_AddCommand_t Cmd_AddCommand;

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* name, CommandCB_t callback, cmd_function_t* data);
extern Cmd_AddServerCommand_t Cmd_AddServerCommand;

typedef void (__cdecl * Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);
extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

typedef void (__cdecl * Cmd_SetAutoComplete_t)(const char* name, const char* path, const char* extension);
extern Cmd_SetAutoComplete_t Cmd_SetAutoComplete;


typedef void(__cdecl * Com_Error_t)(errorParm_s type, const char* message, ...);
extern Com_Error_t Com_Error;

typedef char* (__cdecl * Com_ParseExt_t)(char*);
extern Com_ParseExt_t Com_ParseExt;

typedef char* (__cdecl * Com_ParseExt2_t)(char**);
extern Com_ParseExt2_t Com_ParseExt2;

typedef void (__cdecl * Com_BeginParseSession_t)(const char* why);
extern Com_BeginParseSession_t Com_BeginParseSession;

typedef void (__cdecl * Com_EndParseSession_t)();
extern Com_EndParseSession_t Com_EndParseSession;

typedef void (__cdecl * Com_Printf_t)(int, const char*, ...);
extern Com_Printf_t Com_Printf;

typedef void (__cdecl * Com_PrintError_t)(int, const char*, ...);
extern Com_PrintError_t Com_PrintError;

typedef int (__cdecl * Com_Milliseconds_t)(void);
extern Com_Milliseconds_t Com_Milliseconds;


typedef void (*DB_LoadXAssets_t)(XZoneInfo* data, int count, int unknown);
extern DB_LoadXAssets_t DB_LoadXAssets;

typedef void* (__cdecl * DB_FindXAssetHeader_t)(int type, const char* filename);
extern DB_FindXAssetHeader_t DB_FindXAssetHeader;

typedef dvar_t* (__cdecl * Dvar_RegisterBool_t)(const char* name, bool default, int flags, const char* description);
extern Dvar_RegisterBool_t Dvar_RegisterBool;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat_t)(const char* name, float default, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat_t Dvar_RegisterFloat;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat2_t)(const char* name, float defx, float defy, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat2_t Dvar_RegisterFloat2;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat3_t)(const char* name, float defx, float defy, float defz, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat3_t Dvar_RegisterFloat3;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat4_t)(const char* name, float defx, float defy, float defz, float defw, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat4_t Dvar_RegisterFloat4;

typedef dvar_t* (__cdecl * Dvar_RegisterInt_t)(const char* name, int default, int min, int max, int flags, const char* description);
extern Dvar_RegisterInt_t Dvar_RegisterInt;

typedef dvar_t* (__cdecl * Dvar_RegisterEnum_t)(const char* name, char** enumValues, int default, int flags, const char* description);
extern Dvar_RegisterEnum_t Dvar_RegisterEnum;

typedef dvar_t* (__cdecl * Dvar_RegisterString_t)(const char* name, const char* default, int, const char*);
extern Dvar_RegisterString_t Dvar_RegisterString;

typedef dvar_t* (__cdecl * Dvar_RegisterColor_t)(const char* name, float r, float g, float b, float a, int flags, const char* description);
extern Dvar_RegisterColor_t Dvar_RegisterColor;

typedef dvar_t* (__cdecl * Dvar_FindVar_t)(char* dvar);
extern Dvar_FindVar_t Dvar_FindVar;

typedef char* (__cdecl* Dvar_InfoString_Big_t)(int typeMask);
extern Dvar_InfoString_Big_t Dvar_InfoString_Big;

typedef dvar_t* (__cdecl * Dvar_SetCommand_t)(const char* name, const char* value);
extern Dvar_SetCommand_t Dvar_SetCommand;

typedef int (__cdecl * Dvar_SetStringByName_t)(const char* name, const char* value);
extern Dvar_SetStringByName_t Dvar_SetStringByName;

// Dunno the actual name of this function and I'm too lazy to look it up...
typedef char* (__cdecl * Dvar_GetString_t)(dvar_t* dvar);
extern Dvar_GetString_t Dvar_GetString;

typedef void (__cdecl * FS_FreeFile_t)(void* buffer);
extern FS_FreeFile_t FS_FreeFile;

typedef int (__cdecl * FS_ReadFile_t)(const char* path, char** buffer);
extern FS_ReadFile_t FS_ReadFile;

typedef char** (__cdecl * FS_ListFiles_t)(char* path, char* extension, int noclue, int* amount);
extern FS_ListFiles_t FS_ListFiles;

typedef void (__cdecl * FS_FreeFileList_t)(char** list);
extern FS_FreeFileList_t FS_FreeFileList;

typedef int (__cdecl * FS_FOpenFileAppend_t)(char* file);
extern FS_FOpenFileAppend_t FS_FOpenFileAppend;
extern FS_FOpenFileAppend_t FS_FOpenFileWrite;

typedef int (__cdecl * FS_FOpenFileRead_t)(const char* file, int* fh, int uniqueFile);
extern FS_FOpenFileRead_t FS_FOpenFileRead;

typedef int (__cdecl * FS_FCloseFile_t)(int fh);
extern FS_FCloseFile_t FS_FCloseFile;

typedef bool (__cdecl * FS_WriteFile_t)(char* filename, char* folder, void* buffer, int size);
extern FS_WriteFile_t FS_WriteFile;

typedef int (__cdecl * FS_Write_t)(void* buffer, size_t size, int file);
extern FS_Write_t FS_Write;

typedef int (__cdecl * FS_Read_t)(void* buffer, size_t size, int file);
extern FS_Read_t FS_Read;

typedef int (__cdecl * FS_Seek_t)(int fileHandle, int seekPosition, int seekOrigin);
extern FS_Seek_t FS_Seek;

typedef void (__cdecl * G_LogPrintf_t)(char*, ...);
extern G_LogPrintf_t G_LogPrintf;

typedef void (__cdecl * G_GiveAchievement_t)(char* pchName);
extern G_GiveAchievement_t G_GiveAchievement;

typedef void (__cdecl * MSG_Init_t)(void* msg, void* data, int maxsize);
extern MSG_Init_t MSG_Init;

typedef int (__cdecl * MSG_ReadData_t)(msg_t* msg, char*, size_t);
extern MSG_ReadData_t MSG_ReadData;

typedef int (__cdecl * MSG_ReadLong_t)(msg_t* msg);
extern MSG_ReadLong_t MSG_ReadLong;

typedef short (__cdecl * MSG_ReadShort_t)(msg_t* msg);
extern MSG_ReadShort_t MSG_ReadShort;

typedef __int64 (__cdecl * MSG_ReadInt64_t)(msg_t* msg);
extern MSG_ReadInt64_t MSG_ReadInt64;

typedef char* (__cdecl * MSG_ReadString_t)(msg_t*);
extern MSG_ReadString_t MSG_ReadString;

typedef void (__cdecl * MSG_WriteByte_t)(msg_t* msg, unsigned char);
extern MSG_WriteByte_t MSG_WriteByte;

typedef void (__cdecl * MSG_WriteData_t)(msg_t* msg, char*, size_t);
extern MSG_WriteData_t MSG_WriteData;

typedef void (__cdecl * MSG_WriteLong_t)(msg_t* msg, int);
extern MSG_WriteLong_t MSG_WriteLong;

typedef short (__cdecl * MSG_ReadShort_t)(msg_t* msg);
extern MSG_ReadShort_t MSG_ReadShort;

typedef __int64 (__cdecl * MSG_ReadInt64_t)(msg_t* msg);
extern MSG_ReadInt64_t MSG_ReadInt64;


typedef const char* (__cdecl * NET_AdrToString_t)(netadr_t adr);
extern NET_AdrToString_t NET_AdrToString;

typedef bool (__cdecl * NET_CompareAdr_t)(netadr_t, netadr_t);
extern NET_CompareAdr_t NET_CompareAdr;

typedef bool (__cdecl * NET_StringToAdr_t)(const char*, netadr_t*);
extern NET_StringToAdr_t NET_StringToAdr;

typedef void (__cdecl * SV_GameSendServerCommand_t)(int targetEntity, int a2, const char* command);
extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

typedef void (__cdecl * TeleportPlayer_t)(gentity_t* entity, float* pos, float* orientation);
extern TeleportPlayer_t TeleportPlayer;

typedef bool (__cdecl * Sys_SendPacket_t)(int len, const char* buf, netadr_t adr);
extern Sys_SendPacket_t Sys_SendPacket;

typedef void (__cdecl * Cmd_TokenizeString_t)(char* token);
extern Cmd_TokenizeString_t Cmd_TokenizeString;

typedef void (__cdecl * Cmd_EndTokenizedString_t)();
extern Cmd_EndTokenizedString_t Cmd_EndTokenizedString;

typedef void (__cdecl * Scr_NotifyLevel_t)(short notify, int numArgs);
extern Scr_NotifyLevel_t Scr_NotifyLevel;

typedef short (__cdecl * SL_GetString_t)(const char* string, int a2);
extern SL_GetString_t SL_GetString;

typedef void (__cdecl * Scr_NotifyNum_t)(int number, int type, short notify, int numArgs);
extern Scr_NotifyNum_t Scr_NotifyNum;

typedef void* (__cdecl * R_RegisterFont_t)(const char* asset);
extern R_RegisterFont_t R_RegisterFont;

typedef void (__cdecl * R_AddCmdDrawText_t)(const char* text, int, void* font, float screenX, float screenY, float, float, float rotation, float* color, int);
extern R_AddCmdDrawText_t R_AddCmdDrawText;

typedef void (_cdecl * R_AddCmdDrawStretchPic_t)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, const float *color, void* material);
extern R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;

typedef int (__cdecl * R_TextWidth_t)(const char* text, int maxlength, Font* font);
extern R_TextWidth_t R_TextWidth;

typedef int (__cdecl * UI_TextWidth_t)(const char* text, int flags, void* font, float size);
extern UI_TextWidth_t UI_TextWidth;

typedef void (__cdecl * Steam_JoinLobby_t)(CSteamID, char);
extern Steam_JoinLobby_t Steam_JoinLobby;

typedef char* (__cdecl * SE_Load_t)(char* file, int Unk);
extern SE_Load_t SE_Load;

typedef void (__cdecl * Field_Clear_t)(void* field);
extern Field_Clear_t Field_Clear;

typedef script_t * (__cdecl * LoadScriptFile_t)(const char*);
extern LoadScriptFile_t LoadScriptFile;

typedef int (__cdecl * PC_ReadToken_t)(source_t*, token_t*);
extern PC_ReadToken_t 	PC_ReadToken;

typedef void (__cdecl * FreeMemory_t)(void* buffer);
extern FreeMemory_t FreeMemory;

typedef script_t* (__cdecl * Script_Alloc_t)(int length);
extern Script_Alloc_t Script_Alloc;

typedef void (__cdecl * Script_SetupTokens_t)(script_t* script, void* tokens);
extern Script_SetupTokens_t Script_SetupTokens;

typedef int (__cdecl * Script_CleanString_t)(char* buffer);
extern Script_CleanString_t Script_CleanString;

typedef int (__cdecl * _Reader_t)(int, int); // defaulting to int for now
typedef bool (__cdecl * Image_LoadFromFileWithReader_t)(GfxImage* image, _Reader_t reader);
extern Image_LoadFromFileWithReader_t Image_LoadFromFileWithReader;

typedef void (__cdecl * Image_Release_t)(GfxImage* image);
extern Image_Release_t Image_Release;

typedef FS_ListFiles_t Sys_ListFiles_t;
extern Sys_ListFiles_t Sys_ListFiles;
typedef FS_FreeFileList_t Sys_FreeFileList_t;
extern Sys_FreeFileList_t Sys_FreeFileList;

// other stuff
extern CommandCB_t Cbuf_AddServerText_f;
};

// swap
typedef short (__cdecl * BigShort_t)(short);
extern BigShort_t BigShort;

typedef struct {
	unsigned char ip[4];
	unsigned short	port;
} serverAddress_t;

void playSound(char* sound);
void NET_OutOfBandPrint(int type, netadr_t adr, const char* message, ...);
serverAddress_t natosa(netadr_t address);
netadr_t satona(serverAddress_t address);

extern dvar_t** dvarName;
extern dvar_t** r_mode;

extern char* language;

extern DWORD drawDevStuffHookLoc;
extern DWORD windowedWindowStyleHookLoc;
extern DWORD winMainInitHookLoc;
extern DWORD imageVersionCheckHookLoc;
extern DWORD localizeAssetHookLoc;
extern DWORD SELoadLanguageHookLoc;
extern DWORD SetStringHookLoc;
extern DWORD zoneLoadHookLoc;
extern DWORD ffLoadHook1Loc;
extern DWORD menuFileHookLoc;
extern DWORD scrGetFunctionHookLoc;
extern DWORD scrDeclareFunctionTableEntryLoc;
extern DWORD loadGameOverlayHookLoc;
extern DWORD findSoundAliasHookLoc;
extern DWORD printVersionHookLoc;
extern DWORD weaponFileHookLoc;
extern DWORD vehicleFileHookLoc;
extern DWORD dbAddXAssetHookLoc;
extern DWORD dbAddXAssetHookRet;
extern DWORD getBSPNameHookLoc;
extern DWORD materialLoadHookLoc;

extern DWORD initializeRenderer;
extern DWORD SteamFriendsLoc;
extern DWORD SteamUserStatsLoc;
extern DWORD SteamUserStatsInstanceLoc;

extern source_t **sourceFiles;
extern keywordHash_t **menuParseKeywordHash;

extern int version;

extern gentity_t* g_entities;
extern dvar_t* sv_rconPassword;
extern int* svs_numclients;
extern client_t* svs_clients;

#define CURRENT_ZONE_NAME_159 (char*)(*(DWORD*)0x9DAD80 + 4)
#define CURRENT_ZONE_NAME_177 (char*)(*(DWORD*)0x112A680 + 4)
#define CURRENT_ZONE_NAME_184 (char*)(*(DWORD*)0x9D7800 + 4)
#define CURRENT_ZONE_NAME (version == 159 ? CURRENT_ZONE_NAME_159 : (version == 177 ? CURRENT_ZONE_NAME_177 : CURRENT_ZONE_NAME_184))

extern char* current_zone;
extern bool _allowZoneChange;