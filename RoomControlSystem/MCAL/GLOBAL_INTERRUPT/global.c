/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Global interrupt Drive ***************
***************** Date:  5/8/2023 ******************************************
*/

#include"global.h"
#include "../../UTILS/common_macro.h"

void GLOBAL_interruptEnable(void)
{
	SET_BIT(GLOB_INT_REGISTER,GLOB_INT_BIT);
}
void GLOBAL_interruptDisable(void)
{
	CLEAR_BIT(GLOB_INT_REGISTER,GLOB_INT_BIT);
}
