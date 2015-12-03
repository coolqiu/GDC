#ifndef __PSRAMERES_H__
#define __PSRAMERES_H__ 
#include <stdint.h>
#define FLASH_MEMORY_ABSOLUTE_START_ADRES  0x08000000
#define FLASH_MEMORY_PAGES 128
#define FLASH_MEMORY_PAGE_SIZE 0x800
#define Page_0  0x8000000
#define Page_1  0x8000800
#define Page_2  0x8001000
#define Page_3  0x8001800
#define Page_4  0x8002000
#define Page_5  0x8002800
#define Page_6  0x8003000
#define Page_7  0x8003800
#define Page_8  0x8004000
#define Page_9  0x8004800
#define Page_10 0x8005000
#define Page_11 0x8005800
#define Page_12 0x8006000
#define Page_13 0x8006800
#define Page_14 0x8007000
#define Page_15 0x8007800
#define Page_16 0x8008000
#define Page_17 0x8008800
#define Page_18 0x8009000
#define Page_19 0x8009800
#define Page_20 0x800A000
#define Page_21 0x800A800
#define Page_22 0x800B000
#define Page_23 0x800B800
#define Page_24 0x800C000
#define Page_25 0x800C800
#define Page_26 0x800D000
#define Page_27 0x800D800
#define Page_28 0x800E000
#define Page_29 0x800E800
#define Page_30 0x800F000
#define Page_31 0x800F800
#define Page_32 0x8010000
#define Page_33 0x8010800
#define Page_34 0x8011000
#define Page_35 0x8011800
#define Page_36 0x8012000
#define Page_37 0x8012800
#define Page_38 0x8013000
#define Page_39 0x8013800
#define Page_40 0x8014000
#define Page_41 0x8014800
#define Page_42 0x8015000
#define Page_43 0x8015800
#define Page_44 0x8016000
#define Page_45 0x8016800
#define Page_46 0x8017000
#define Page_47 0x8017800
#define Page_48 0x8018000
#define Page_49 0x8018800
#define Page_50 0x8019000
#define Page_51 0x8019800
#define Page_52 0x801A000
#define Page_53 0x801A800
#define Page_54 0x801B000
#define Page_55 0x801B800
#define Page_56 0x801C000
#define Page_57 0x801C800
#define Page_58 0x801D000
#define Page_59 0x801D800
#define Page_60 0x801E000
#define Page_61 0x801E800
#define Page_62 0x801F000
#define Page_63 0x801F800
#define Page_64 0x8020000
#define Page_65 0x8020800
#define Page_66 0x8021000
#define Page_67 0x8021800
#define Page_68 0x8022000
#define Page_69 0x8022800
#define Page_70 0x8023000
#define Page_71 0x8023800
#define Page_72 0x8024000
#define Page_73 0x8024800
#define Page_74 0x8025000
#define Page_75 0x8025800
#define Page_76 0x8026000
#define Page_77 0x8026800
#define Page_78 0x8027000
#define Page_79 0x8027800
#define Page_80 0x8028000
#define Page_81 0x8028800
#define Page_82 0x8029000
#define Page_83 0x8029800
#define Page_84 0x802A000
#define Page_85 0x802A800
#define Page_86 0x802B000
#define Page_87 0x802B800
#define Page_88 0x802C000
#define Page_89 0x802C800
#define Page_90 0x802D000
#define Page_91 0x802D800
#define Page_92 0x802E000
#define Page_93 0x802E800
#define Page_94 0x802F000
#define Page_95 0x802F800
#define Page_96 0x8030000
#define Page_97 0x8030800
#define Page_98 0x8031000
#define Page_99 0x8031800
#define Page_100 0x8032000
#define Page_101 0x8032800
#define Page_102 0x8033000
#define Page_103 0x8033800
#define Page_104 0x8034000
#define Page_105 0x8034800
#define Page_106 0x8035000
#define Page_107 0x8035800
#define Page_108 0x8036000
#define Page_109 0x8036800
#define Page_110 0x8037000
#define Page_111 0x8037800
#define Page_112 0x8038000
#define Page_113 0x8038800
#define Page_114 0x8039000
#define Page_115 0x8039800
#define Page_116 0x803A000
#define Page_117 0x803A800
#define Page_118 0x803B000
#define Page_119 0x803B800
#define Page_120 0x803C000
#define Page_121 0x803C800
#define Page_122 0x803D000
#define Page_123 0x803D800
#define Page_124 0x803E000
#define Page_125 0x803E800
#define Page_126 0x803F000
#define Page_127 0x803F800
//#define Page_128 0x8040000 не существует во флеш !!! приведен для проверки
#define flash_save_interval 200 
typedef struct _parameters_t
{
	float value;
	char param_id[17];
	uint8_t param_type;
} parameters_t;
typedef union _convert_params_to_t
{
	float float32;
	uint32_t uint32;
	uint16_t uint16;
	uint8_t  uint8;
	int32_t  int32;
	int16_t  int16;
	int8_t   int8;
}convert_params_to_t;
extern       parameters_t parameter_RW[455];
extern const parameters_t parameter_RO[455];
extern uint16_t total_param_count;
extern uint8_t flash_saving_timer;
extern convert_params_to_t convert_to;
extern float yaw_offset;
extern float pitch_offset;
void init_param_arry(void);
void write_params_to_flash(void);
void reload_parameters(void);
uint16_t parameters_contain(char string[16]);
#endif
