//;+------------------------------------------------------------------+
//;|       $Workfile:: countbits.c                $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 15/12/11 1:38p                                 $
//;|        $Archive:: /@C18/obj/bitops/countbits.c                   $
//;+------------------------------------------------------------------+

unsigned char countbits(unsigned char b)
{
	unsigned char count;
	
	for (count = 0; b != 0; count++)
	{
		b &= b - 1; // this clears the LSB-most set bit
	}
	
	return (count);
}
