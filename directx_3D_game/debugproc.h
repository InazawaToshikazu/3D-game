//=============================================================================
//
// デバッグ処理 [debugproc.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

//=============================================================================
// ヘッダファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// ライブラリのリンク
//=============================================================================

//=============================================================================
// デバッグ処理クラス
//=============================================================================
class CDebugProc
{
	//公開メンバ
	public:
		CDebugProc();			//コンストラクタ
		~CDebugProc();			//デストラクタ
	
		void Init(void);		//初期化
		void Uninit(void);		//終了
	
		static void Print(char *fmt,...);
		static void Draw(void);		//描画
	
		static bool IsEnableDisp(void){ return m_bDisp; }
		static void EnableDisp(bool bDisp){ m_bDisp = bDisp; }
	
	//非公開メンバ
	private:
		static LPD3DXFONT m_pD3DXFont;
		static char m_aStr[1024];
	
		static bool m_bDisp;
};

#endif