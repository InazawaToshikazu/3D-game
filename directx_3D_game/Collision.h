//-----------------------------------------------------------------------------
//
// �����蔻�菈�� : collision.h
// Author : ���V�r�a
//
//-----------------------------------------------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_

//------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �\����
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �O���Q��
//------------------------------------------------------------------------
class CRenderer;
class CScene;
//------------------------------------------------------------------------
// �N���X
//------------------------------------------------------------------------
class CCollision
{
public : 
	CCollision( void );		// �R���X�g���N�^
	~CCollision();			// �f�X�g���N�^

	//--  ���Ƌ�  --//
	bool SphereToSphere3D( const D3DXVECTOR3& pos0 , float radius0 , const D3DXVECTOR3& pos1 , float radius1 );
	bool SphereToSphere3D( CScene& object0 , CScene& object1 , float radius0 , float radius1 );
	bool SphereToSphereXZ( const D3DXVECTOR3& pos0 , const D3DXVECTOR3& pos1 , float radius0 , float radius1 );

	//--  ���Ƌ�`  --//
	bool CircleToRectangle2D( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth );
	bool CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth );
	bool CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , CScene& object , float fHeight , float fWidth );

	//--  ��`�Ƌ�`  --//
	bool RectangleToRectangle3D( const D3DXVECTOR3& pos0 , float fHeight0 , float fWidth0 , const D3DXVECTOR3& pos1 , float fHeight1 , float fWidth1 );

	//--  �O�ς̓����蔻��  --//
	bool LinetoLineXZ( D3DXVECTOR3 pos0st , 
					   D3DXVECTOR3 pos0ed ,
					   D3DXVECTOR3 pos1st ,
					   D3DXVECTOR3 pos1ed ,
					   D3DXVECTOR3 *pPosCross ,
					   float *pfRote ,
					   D3DXVECTOR3 *pVecReflect );


private : 

protected : 
};

#endif // _COLLISION_H_

// END