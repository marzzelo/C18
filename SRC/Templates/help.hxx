/*-- Shortcuts -------------------------------------------------------------*/

^1 		Set/Clear BreakPoint
^2 		Run to Cursor
^3 		Uppercase
^4		Lowercase
^5		Comment Block
^6		Uncomment block
^7
^8
^9
^0

/*--------------------------------------------------------------------------*/
^M		Match
^Q		Goto Locator
^G		Goto

/*--------------------------------------------------------------------------*/
^Sh 1	Set PC at cursor
^Sh 2	Run to cursor
^Sh 3	Expand All
^Sh 4	Expand Block
^Sh 5	Collapse All
^Sh 6	Collapse Block
^Sh 7	
^Sh 8	Clear Bookmarks
^Sh 9	Bookmark
^Sh 0

/*--------------------------------------------------------------------------*/
^Sh C	Format Comment
^Sh Y	Delete line

/*--------------------------------------------------------------------------*/
Alt 1	
Alt 2	
Alt 3	
Alt 4	Go Backward
Alt 5	
Alt 6	Go Forward
Alt 7	
Alt 8	
Alt 9	
Alt 0	

/*--------------------------------------------------------------------------*/
Alt F10		Quick Build
/*==========================================================================*/





/*-- Nombres de argumentos -------------------------------------------------*/
	    [arg_ATcmd]  [arg_stat]    [arg_cid]
[line1] +CMGR:       "REC UNREAD", "+5493515923672","Mr. Jones","95/07/03,17:38:15+04"

        [arg_usrcmd] [arg_usr_p1]
[line2] pri          1234"

[line3] OK






/*-- Lock Interrupts -------------------------------------------------------*/
uint8_t intKey;

QF_INT_LOCK(intKey); 
QF_INT_UNLOCK(intKey); 






/*-- Arguments -------------------------------------------------------------*/
#define arg_ATcmd 	line1[0]
#define arg_stat	line1[0]
#define arg_cid		line1[0]

#define arg_usrcmd	line2[0]
#define arg_usr_p1	line2[1]
#define arg_usr_p2	line2[2]
#define arg_usr_p3	line2[3]





/*-- Estados -------------------------------------------------------------- */
static QState AODeco_initial			(AODeco *me, QEvent const *e);

static QState AODeco_initModem			(AODeco *me, QEvent const *e);
static QState AODeco_sampling			(AODeco *me, QEvent const *e);
static QState AODeco_registering		(AODeco *me, QEvent const *e);
	static QState AODeco_antennaLevel	(AODeco *me, QEvent const *e);
    static QState AODeco_wHeader		(AODeco *me, QEvent const *e);
    	static QState AODeco_prepCMGL	(AODeco *me, QEvent const *e);
    	static QState AODeco_prepRTCT	(AODeco *me, QEvent const *e);
    static QState AODeco_wCMSS			(AODeco *me, QEvent const *e);    
    static QState AODeco_sendingFromSto	(AODeco *me, QEvent const *e);
    static QState AODeco_delREC			(AODeco *me, QEvent const *e);






/*--------------------------------------------------------------------------*/
  
  
  