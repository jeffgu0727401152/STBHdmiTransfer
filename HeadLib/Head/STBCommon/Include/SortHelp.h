/*
���ߣ�kyo wang
�����ʹ�ò������˴��룬�����뱣����ע�Ͳ���
*/
#ifndef __SORT_HELP_HEADER__
#define __SORT_HELP_HEADER__

/************************************************************************/
/* sort help function                                                   */
/************************************************************************/
	// lParam1 : item 1 to be compared
	// lParam2 : item 2 to be compared
	// lParamSort : 
	//	    loword: Asce or Desc
	//		hiword: ignore case or not
	// uUserData :
	//		userdata will be ignore in these help sort functions

	int SortCmpStringW(
		const void* lParam1,
		const void* lParam2,
		const UINT64 lParamSort,
		const UINT64 uUserData);

	int SortCmpStringA(
		const void* lParam1,
		const void* lParam2,
		const UINT64 lParamSort,
		const UINT64 uUserData);

	template <class T>
	inline int SortCmpDigital(
		T digital1,
		T digital2,
		const UINT64 lParamSort,
		const UINT64 uUserData)
	{
		if (IS_SORTPARAM_ASCE(lParamSort))
		{
			return ((digital1==digital2) ? 0 : ((digital1<digital2) ? -1 : 1));
		}
		else
		{
			return ((digital1==digital2) ? 0 : ((digital1<digital2) ? 1 : -1));
		}
	}

/************************************************************************/
/* sort help function                                                   */
/************************************************************************/
#endif
