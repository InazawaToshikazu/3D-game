//-----------------------------------------------------------------------------
//
// �����蔻�菈�� : collision.cpp
// Author : ���V�r�a
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------
#include "main.h"
#include "Renderer.h"
#include "Collision.h"

#include <math.h>
#include "scene.h"

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
// �ÓI�����o�ϐ�
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------

//-------------------------------------------------------------------
// �֐��� : �R���X�g���N�^
//
// ����   : �Ȃ�
//-------------------------------------------------------------------
CCollision::CCollision(void)
{
}

//-------------------------------------------------------------------
// �֐��� : �f�X�g���N�^
//
// ����   : �Ȃ� 
//-------------------------------------------------------------------
CCollision::~CCollision(void)
{
}

//-------------------------------------------------------------------
// �֐��� : ���Ƌ��̓����蔻��
//
// ����   : CSCENE& object0 : �I�u�W�F�N�g0
// ����   : CSCENE& object1 : �I�u�W�F�N�g1
// ����   : float radius0 : ���a
// ����   : float radius1 : ���a
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::SphereToSphere3D(CScene& object0,CScene& object1,float radius0,float radius1)
{
	//--  �v�Z�p  --//
	D3DXVECTOR3 pos0 = object0.GetPos();
	D3DXVECTOR3 pos1 = object1.GetPos();

	//--  �~�̔���p  --//
	D3DXVECTOR3 pos = pos0 - pos1 ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.y * pos.y ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// �֐��� : ���Ƌ��̓����蔻��
//
// ����   : VECTOR3& pos0 : ���W0
// ����   : VECTOR3& pos1 : ���W1
// ����   : float radius0 : ���a
// ����   : float radius1 : ���a
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::SphereToSphere3D( const D3DXVECTOR3& pos0 , float radius0 , const D3DXVECTOR3& pos1 , float radius1 )
{
	//--  �~�̔���p  --//
	D3DXVECTOR3 pos ;
	pos.x = pos0.x - pos1.x ;
	pos.y = pos0.y - pos1.y ;
	pos.z = pos0.z - pos1.z ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.y * pos.y ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// �֐��� : ���Ƌ��̓����蔻��
//
// ����   : VECTOR3& pos0 : ���W0
// ����   : VECTOR3& pos1 : ���W1
// ����   : float radius0 : ���a
// ����   : float radius1 : ���a
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::SphereToSphereXZ( const D3DXVECTOR3& pos0 , const D3DXVECTOR3& pos1 , float radius0 , float radius1 )
{
	//--  �~�̔���p  --//
	D3DXVECTOR3 pos ;
	pos.x = pos0.x - pos1.x ;
	pos.y = pos0.y - pos1.y ;
	pos.z = pos0.z - pos1.z ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// �֐��� : �~�Ƌ�`
//
// ����   : VECTOR3& pos0 : �I�u�W�F�N�g0
// ����   : float radius : ���a
// ����   : VECTOR3& pos1 : �I�u�W�F�N�g1
// ����   : float fHeight : �c��
// ����   : float fWidth : ����
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::CircleToRectangle2D( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth )
{
	D3DXVECTOR3 pos[ 4 ];

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].y = pos1.y + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].y = pos1.y + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 2 ].y = pos1.y - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 3 ].y = pos1.y - fHeight * 0.5f ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		if( SphereToSphere3D( pos0 , radius , pos[ i ] , 0.1f ) )
		{
			return true ;
		}
	}

	return false ;
}

//-------------------------------------------------------------------
// �֐��� : �~�Ƌ�`
//
// ����   : VECTOR3& pos0 : �I�u�W�F�N�g0
// ����   : float radius : ���a
// ����   : VECTOR3& pos1 : �I�u�W�F�N�g1
// ����   : float fHeight : �c��
// ����   : float fWidth : ����
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth )
{
	//VECTOR3 pos0 = object0.GetPos();
	//VECTOR3 pos1 = object1.GetPos();

	D3DXVECTOR3 pos[ 4 ];		// ���_
	D3DXVECTOR3 VecLine ;		// �x�N�g��
	D3DXVECTOR3 VecToTarget ;	// �^�[�Q�b�g

	for( int i = 0 ; i < 4 ; i++ )
	{
		pos[ i ] = D3DXVECTOR3( 0 , 0 , 0 );
	}

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 2 ].z = pos1.z - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 3 ].z = pos1.z - fHeight * 0.5f ;

	//VECTOR3 offset = pos0 - pos1 ;	// �I�t�Z�b�g
	//pos0.x = pos1.x + ( cosf( -pos1->GetRot().y ) * offset.x ) + sinf( -pos1->GetRot().y ) * offset.z ;
	//pos0.z = pos1.z + ( cosf( -pos1->GetRot().y ) * offset.z ) + sinf( -pos1->GetRot().y ) * offset.x ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		VecLine = pos[ ( 1 + i ) %4 ] - pos[ i ];

		VecToTarget.x = pos0.x - pos[ i ].x ;
		VecToTarget.y = pos0.y - pos[ i ].y ;
		VecToTarget.z = pos0.z - pos[ i ].z ;

		//--  �͈͊O�ɍs������  --//
		if( VecToTarget.x * VecLine.z - VecToTarget.z * VecLine.x < 0.001f )
		{
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------
// �֐��� : �~�Ƌ�`
//
// ����   : VECTOR3& pos0 : ���W
// ����   : float radius : ���a
// ����   : CSCENE& object : �I�u�W�F�N�g
// ����   : float fHeight : �c��
// ����   : float fWidth : ����
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , CScene& object , float fHeight , float fWidth )
{
	//VECTOR3 pos0 = object0.GetPos();
	D3DXVECTOR3 pos1 = object.GetPos();
	D3DXVECTOR3 rot =  object.GetRot();

	D3DXVECTOR3 pos[ 4 ];		// ���_
	D3DXVECTOR3 VecLine ;		// �x�N�g��
	D3DXVECTOR3 VecToTarget ;	// �^�[�Q�b�g�x�N�g��
	D3DXVECTOR3 target ;		// �^�[�Q�b�g

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 2 ].z = pos1.z - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 3 ].z = pos1.z - fHeight * 0.5f ;

	D3DXVECTOR3 offset ; // = pos0 - pos1 ;	// �I�t�Z�b�g
	offset.x = pos0.x - pos1.x ;
	offset.y = pos0.y - pos1.y ;
	offset.z = pos0.z - pos1.z ;

	target.x = pos1.x + cosf( rot.y ) * offset.x + sinf( rot.y ) * offset.z ;
	target.z = pos1.z + cosf( rot.y ) * offset.z + sinf( rot.y ) * offset.x ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		VecLine = pos[ ( 1 + i ) % 4 ] - pos[ i ];
		VecToTarget = target - pos[ i ];

		//--  �͈͊O�ɍs������  --//
		if( VecToTarget.x * VecLine.z - VecToTarget.z * VecLine.x < 0.0f )
		{
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------
// �֐��� : ��`�Ƌ�`
//
// ����   : CSCENE& pos0 : �I�u�W�F�N�g0
// ����   : float fHeight : �c��
// ����   : float fWidth : ����
// ����   : CSCENE& pos1 : �I�u�W�F�N�g1
// ����   : float fHeight : �c��
// ����   : float fWidth : ����
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool RectangleToRectangle3D( CScene& pos0 , float fHeight0 , float fWidth0 , CScene& pos1 , float fHeight1 , float fWidth1 )
{
	//VECTOR3 p0 = object0.GetPos();
	//VECTOR3 p1 = object1.GetPos();

	//VECTOR3 pos0[ 4 ];
	//VECTOR3 pos1[ 4 ];

	//pos0[ 0 ].x = p0.x - fWidth0 * 0.5f ;
	//pos0[ 0 ].y = p0.y + fHeight0 * 0.5f ;
	//			 
	//pos0[ 1 ].x = p0.x + fWidth0 * 0.5f ;
	//pos0[ 1 ].y = p0.y + fHeight0 * 0.5f ;
	//			 
	//pos0[ 2 ].x = p0.x - fWidth0 * 0.5f ;
	//pos0[ 2 ].y = p0.y - fHeight0 * 0.5f ;
	//			
	//pos0[ 3 ].x = p0.x + fWidth0 * 0.5f ;
	//pos0[ 3 ].y = p0.y - fHeight0 * 0.5f ;

	//pos1[ 0 ].x = p1.x - fWidth0 * 0.5f ;
	//pos1[ 0 ].y = p1.y + fHeight0 * 0.5f ;
	//		
	//pos1[ 1 ].x = p1.x + fWidth0 * 0.5f ;
	//pos1[ 1 ].y = p1.y + fHeight0 * 0.5f ;
	//
	//pos1[ 2 ].x = p1.x - fWidth0 * 0.5f ;
	//pos1[ 2 ].y = p1.y - fHeight0 * 0.5f ;

	//pos1[ 3 ].x = p1.x + fWidth0 * 0.5f ;
	//pos1[ 3 ].y = p1.y - fHeight0 * 0.5f ;

	////--  Z�̔���  --//
	//if( g_Bullet[ nBulletNum ].object.pos.z - HITBULLETLENGEZ < pEnemyBox[ nEnemyNum ].object.pos.z + HITBULLETLENGEZ && 
	//	g_Bullet[ nBulletNum ].object.pos.z + HITBULLETLENGEZ > pEnemyBox[ nEnemyNum ].object.pos.z - HITBULLETLENGEZ )
	//{
	//	//--  X�̔���  --//
	//	if( g_Bullet[ nBulletNum ].object.pos.x - HITBULLETLENGEX < pEnemyBox[ nEnemyNum ].object.pos.x + HITBULLETLENGEX && 
	//		g_Bullet[ nBulletNum ].object.pos.x + HITBULLETLENGEX > pEnemyBox[ nEnemyNum ].object.pos.x - HITBULLETLENGEX )
	//	{
	//		//--  Y�̔���  --//
	//		if( g_Bullet[ nBulletNum ].object.pos.y - HITBULLETLENGEY < pEnemyBox[ nEnemyNum ].object.pos.y + HITBULLETLENGEY && 
	//			g_Bullet[ nBulletNum ].object.pos.y + HITBULLETLENGEY > pEnemyBox[ nEnemyNum ].object.pos.y - HITBULLETLENGEY )
	//		{
	//			//--  �폜  --//
	//			DeleteEnemyBox( nEnemyNum );
	//			DeleteBullet( nBulletNum );

	//			//--  ����  --//
	//			SetExplosion( g_Bullet[ nBulletNum ].object.pos );

	//			//--  �T�E���h  --//
	//			PlaySound( SOUND_LABEL_SE_EXPLOSION01 );

	//			AddScore( 1000 );
	//		}
	//	}
	//}

	return false ;
}

//-------------------------------------------------------------------
// �֐��� : �O�ς̓����蔻��
//
// ����   : VECTOR3 pos0st		: ����̐����̎n�_
// ����   : VECTOR3 pos0ed		: ����̐����̏I�_
// ����   : VECTOR3 pos1st		: ��������̐����̎n�_
// ����   : VECTOR3 pos1ed		: ��������̐����̏I�_
// ����   : VECTOR3 *pPosCross	: out : ��_�̌�_
// ����   : float *pRote			: out : �n�_�����_�܂ł̒����̐����̒���
// ����   : VECTOR3 *pVecReflect: out : ���˃x�N�g��
// �Ԃ�l : �^�U
//-------------------------------------------------------------------
bool CCollision::LinetoLineXZ( D3DXVECTOR3 pos0st , 
							   D3DXVECTOR3 pos0ed ,
							   D3DXVECTOR3 pos1st ,
							   D3DXVECTOR3 pos1ed ,
							   D3DXVECTOR3 *pPosCross ,
							   float *pfRote ,
							   D3DXVECTOR3 *pVecReflect )
{
	D3DXVECTOR3 vec0 , vec1 , vec2 ;

	vec0 = pos0ed - pos0st ;
	vec1 = pos1ed - pos1st ;
	vec2 = pos0st - pos1st ;

	//--  vec0 - vec1�̐����̊O��( vec0��vec1���E( �}�C�i�X )�Ȃ� )  --//
	float fCrossProduct_0_1 = vec0.z * vec1.x - vec0.x * vec1.z ;

	if( fCrossProduct_0_1 == 0.0f )
	{
		return false ;
	}

	//--  vec1 - vec0�̐����̊O��( vec1��vec0���E( �}�C�i�X )�Ȃ� )  --//
	float fCrossProduct_1_2 = vec1.z * vec1.x - vec1.x * vec2.z ;
	
	float fRate_1_2 = fCrossProduct_1_2 / fCrossProduct_0_1 ;

	//--  �������N���X���ɂ��邩  --//
	if( fRate_1_2 >= 0.0f && fRate_1_2 <= 1.0f )
	{
		//--  vec0 - vec1�̐����̊O�ςɑ΂���vec2 - vec0�̐����̊O�ς̓��������Z�o  --//
		//--  vec1��vec0�̉E�� : 1.0����  --//
		//--  vec1��vec0�̍��� : 0��艺  --//

		if( pPosCross != NULL )
		{
			//--  ��_  --//
			*pPosCross = pos0st + vec0 * fRate_1_2 ;
			//*pPosCross = pos1st + vec1 * fRate_0_2 ;

			if( pfRote != NULL )
			{
				//--  ���ρ@�������m�̌����܂ł̓�����  --//
				*pfRote = fRate_1_2 ;
			}

			//--  ����  --//
			if( pVecReflect != NULL )
			{
				D3DXVECTOR3 vecMove , vecLine ;

				vecMove = pos1ed - pos1st ;
				vecLine = pos0ed - pos0st ;

				//--  ��������������m�̓��ώZ�o  --//
				float fDotProduct = vecLine.x * vecMove.x + vecLine.z * vecMove.z ;

				//--  ������������̂Ȃ��p( a*b = |->a||->b|cos�� )  --//
				float fValueLine = sqrt( vecLine.x * vecLine.x + vecLine.z * vecLine.x );
				float fValueMove = sqrt( vecMove.x * vecMove.x + vecMove.z * vecMove.x );

				float fAngle = acosf( fDotProduct / ( fValueMove * fValueLine ) );

				//--  ���˃x�N�g��  --//
				D3DXVECTOR3 vecMoveNew( cosf( fAngle ) * vecLine.z + sinf( fAngle ) * vecLine.x ,
										0.0f , 
										cosf( fAngle ) * vecLine.z + sinf( fAngle ) * vecLine.x );

				D3DXVec3Normalize( &vecMoveNew , &vecMoveNew );

				*pVecReflect = vecMoveNew ;
			}

			return true ;
		}
	}
	return false ;
}

//-------------------------------------------------------------------
// �֐��� : 
//
// ����   : 
// �Ԃ�l : 
//-------------------------------------------------------------------


// END
