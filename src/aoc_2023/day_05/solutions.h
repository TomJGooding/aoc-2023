#include <stddef.h>

typedef struct Range {
    unsigned int start;
    unsigned int stop;
} Range;

typedef struct MapLine {
    Range dest_range;
    Range src_range;
} MapLine;

typedef enum MapType {
    SEED_TO_SOIL,
    SOIL_TO_FERT,
    FERT_TO_WTR,
    WTR_TO_LGT,
    LGT_TO_TMP,
    TMP_TO_HMD,
    HMD_TO_LOC,
    TOTAL_MAP_TYPES
} MapType;

typedef struct Map {
    MapType type;
    MapLine lines[64];
    size_t lines_count;
} Map;

unsigned int solve_part_one(char const *filename);
