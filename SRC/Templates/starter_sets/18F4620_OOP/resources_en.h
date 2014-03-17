//;+------------------------------------------------------------------+
//;|       $Workfile:: resources_en.h             $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 16/06/11 8:41p                                 $
//;|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/reso $
//;+------------------------------------------------------------------+
 
// S T R I N G S    D E    M E N S A J E S 
#define CHR_YES						'Y'
#define CHR_NO						'N'
#define CHR_no						'n'
#define CHR_LINK					'L'
#define CHR_link					'L'
#define CHR_UNLINK					'u'
#define CHR_DISABLE					'D'
#define CHR_ENABLE					'E'
#define CHR_PERMANENT				'P'
#define CHR_ANULLED					'A'
#define CHR_INTERIOR				'I'

#define CHR_CONDITIONAL				'C'
#define CHR_ALWAYS					'A'
#define CHR_NEVER					'N'


#define TXT_USER_DISABLED			"Disabled Account"
#define	TXT_UNKNOWN_COMMAND__s		"Unknown command: \"%s...\""
#define TXT_AUTHORIZED__s			"NVCONTROL NV6410+: Account %s authorized (loc.1)"
#define TXT_NO_NEW_USERS_ALLOWED	"No new users allowed"
#define TXT_ALREADY_REGD__d			"Already registered (loc.%d)"
#define	TXT_MEMORY_FULL				"Memory full"
#define TXT_INCORRECT_NUMBER		"Err: bad ph.number"
#define TXT_AUTHORIZED__sd			"NVCONTROL NV6410+: Account %s authorized (loc.%d)"
#define TXT_MODEL					"NV6410+ FWD: "
#define TXT_ANTENNA_LEVEL__sd		"Signal Level: %s (%d)"
#define TXT_VAR_DUMP__				"Free mem: %d" \
									"\r\nCall-mngd Output: %s (Tone: %c, SMS: %c)" \
									"\r\nBAT Lvl: %s (%d mV) AC:%s" \
									"\r\nAC fail tol: %d min" \
									"\r\nPrim.Pwd: %s" \
									"\r\nSecn.Pwd: %s" \
									"\r\nSMS cnt: %d" \
									"\r\nSMS dly: %d sec" \
									"\r\nHora: %04d"

#define TXT_ZONES__c				"Zones: (Reports: %c, ARMED: %c)"
#define TXT_OUTPUTS					"Outputs: Alias(Ton,Toff,act):now"
#define TXT_LINKS					"Links:\r\nZN:   123456"
#define TXT_ERROR_CHECK				"Fmt.Err: Opt(z,s,e,v,c)"
#define TXT_USERS					"USERS:\r\n"
#define TXT_USRTOOBIG				"Err: Usrs(1..50)"
#define TXT_ERR_SAL_1_8				"Fmt.Err: Out(1..8)"
#define TXT_ERR_NIVEL				"Parm.Err: Levels(1..4)"
#define TXT_ERR_ACCESO				"Parm.Err: Opt(+-z,i,o,l,e,b,v)"
#define TXT_ERR_SAL_1_8_ALIAS		"Fmt.Err: Out(1..8),Alias"
#define TXT_OP_NO_AUT				"Unauthorized Option"
#define TXT_OUTPUT_TONOFF__sdd		"Output %s: Ton=%ds, Toff=%ds"
#define TXT_TONOFF_ERROR			"Err: Tmax=32767 sec"
#define TXT_OUTPUT_STATE__bb		"12345678 (Outputs)\r\n" \
									"%s (Before)\r\n" \
									"%s (After)" 

#define TXT_OUT_LINK_IN__ss			"Output %s %s Input %s"
#define TXT_ERR_OUT					"Fmt.Err: Opt(t,sn,eq)"
#define TXT_LINE_FAIL_TOL__s		"AC Fail Tolerance: %s min"
#define TXT_BATT_CANCELLED			"AC Reports cancelled"
#define TXT_ERR_PER_CONS			"Fmt.Err: Opt(tol)"
#define TXT_Z24HS__b				"123456 (24hr Zones)\r\n" \
									"%s" 
#define TXT_ZINT__b					"123456 (Int Zones)\r\n" \
									"%s" 									
#define TXT_CUSTOM_MSG__ds			"Custom msg%d: \"%s\""
#define TXT_MSG_TOOLONG				"Err: Msg max 40, min 3 chars"
#define TXT_ERR_ZONE				"Fmt.Err: Opt(m,n,p,24)"
#define TXT_ERR_OPC_SN				"Fmt.Err: Opt(y,n)"

#define TXT_ERR_ZON_1__6_ALIAS		"Fmt.Err: Zon(1..6),Alias"
#define TXT_ERR_ZON_1__6			"Fmt.Err: Zon(1..6)"
#define TXT_ARMED__sds				"ARMED (%s, %d: %s)"
#define TXT_FULL_ARMED				"FULLY ARMED"
#define TXT_ARM_INTERIOR			"INTERIOR"
#define TXT_MANUAL_ARMED			"FULLY ARMED"  // (FIE)
#define TXT_DISARMED__ds			"DISARMED (%d: %s)"
//#define MAIL_TXT_DISARMED__ds		"FYI: DISARMED (%d: %s)"
#define TXT_ERR_KEYWORD				"Err: Password len = 3 to 10 chr."
#define TXT_KEYWORD_CHGD__ss		"Password chgd OK: %s -> %s"

// Mail
#define TXT_MAIL_CONFIRM			"e-mail updated"
#define TXT_MAIL_DISABLE			"e-mail disabled"
#define TXT_MAIL_ENABLE				"e-mail enabled"
#define TXT_UNCOMPLETE_MAIL			"Fmt: email (address) (gateway-send) (gateway-rcv)"
#define TXT_MAILSETTINGS			"e-mail settings:\r\ne-mail: %s\r\nsend: %s\r\nreceive: %s"

// Timer
#define TXT_TIM_DISABLED			"AUX INPUT DISABLED (%d: %s)"

// Passwords
#define	TXT_ERR_CLAVE_INC			"Err: Bad password format"
#define TXT_USR_INEXISTENTE__d		"User %d unknown"
#define TXT_MODIF_OK 				"Value changed Ok"
#define TXT_ERR_PASSWORDS			"Fmt.Err: Opt(p,s)"

// Captures
#define TXT_CAPTURES				"Keywords to capture:"
#define TXT_UNCOMPLETE_COMMAND		"Bad Command Format"
#define TXT_ERR_CAPTURE				"Err: capt 1..5"
#define TXT_CAPTURE_CONFIRM__ds		"Capture %d --> %s"

// Reports
#define TXT_ERR_REPORTS				"Fmt.Err: Opt(y,n,c)"
#define TXT_REPORT_CONFIRM__c		"Reports -> %c"
#define TXT_NEW_USERS_ALLOWED		"New users allowed"
#define TXT_NEW_USERS_DISALLOWED	"No new users allowed"

#define TXT_ALIAS_NOT_FOUND			"Missing alias"
#define TXT_ZALIAS_CONFIRM__ds		"Zone %d --> %s"
#define TXT_SALIAS_CONFIRM__ds		"Output %d --> %s"
#define TXT_ERR_ALIAS				"Err: Opt(i,o)"
#define TXT_ALL_ERASED				"All users erased"
#define TXT_USR_ERASED__d			"User %d erased"
#define TXT_QUEUE_CLEARED			"Message Queue Reset"
#define TXT_ERR_FORWARD_NUM			"Format: Send (PhN) \"msg\""
#define TXT_ERR_FORWARD_MSG			"ERR: missing cust message"
#define TXT_OUTPUT_OFF				"OUTPUT OFF"
#define TXT_OUTPUT_ON				"OUTPUT ON"

// Batería y Linea 220
#define TXT_220LINE_FAIL			"AC FAIL"
#define TXT_220LINE_RESTORE			"AC RESTORED"
#define TXT_ACFAIL					"FAIL"
#define TXT_ACOK					"OK"
#define TXT_LOW_BATTERY				"Battery low: %d mV"
#define TXT_BATTLINK__d				"Batt Low --> output %d"
#define TXT_BATTUNLINK__d			"Batt Low -/-> output %d"
#define TXT_LEVEL_GOOD				"GOOD"
#define TXT_LEVEL_REGULAR			"REGULAR"
#define TXT_LEVEL_LOW				"LOW"


#define TXT_DEFAULT_CUSTOM_MSG		"Zone * reports OPEN"
#define	TXT_ACCESS_MODIFIED			"Access (%c) for user %d changed"
#define TXT_VCALL_CNCLLD			"aux calls disabled"
#define TXT_VCALL_ENABLD			"aux calls enabled"
#define TXT_USER_UNKNOWN__d			"User %d unknown"

// S T R I N G S   D E   C O M A N D O S 

#define TXT_PRI				"PRI" //mary
#define TXT_SEC 			"LOG" //in    
#define TXT_NIV 			"LEV" //el
#define TXT_VER				"CHE" //ck
#define TXT_SAL				"OUT" //put
#define TXT_ZON				"INP" //ut
#define TXT_AUD				"AUD" //io
#define TXT_ACT				"ARM" //ed
#define TXT_DES				"DIS" //armed
#define TXT_LIS				"LIS" //t
#define TXT_ALI				"ALI" //as
#define TXT_KEY				"CAP" //ture
#define TXT_ENV				"SEN" //d
#define TXT_CLA				"PAS" //word
#define TXT_REG				"REG" //ister
#define TXT_BOR				"DEL" //ete
#define TXT_CAN				"CAN" //cel
#define TXT_ACC				"ACC" //ess
#define TXT_REP				"REP" //ort
#define TXT_VOZ				"VOI" //ce
#define TXT_PER				"PER" //iod
#define TXT_RST 			"RST" //reset
#define TXT_TIM				"AUX" // llave auxiliar
#define TXT_MAI				"EMA" // mail
#define TXT_ALA				"ALA" // rm

