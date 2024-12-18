#include "DxLib.h"
#include "Camera.h"
#include "Player/Player.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include <math.h>
#include <Effekseer/Effekseer.h>
#include "Input/KeyBoard/InputKeyBoard.h"
#include <Input/GamePad/GamePad.h>
#include <Input/Mouse/Mouse.h>
#include <Input/Input.h>
#include <Common.h>


namespace BOUDAMA
{
	//カメラ初期化関数
	void Camera::Init(void)
	{
		// カメラの設定
		SetCameraNearFar(1.0f, 27000.0f);

		SetupCamera_Perspective(MyMath::PI_OVER_THREE);

		pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };	//カメラ位置
		target_ = { 0.0f, 0.0f, 0.0f };												//注視点
		up_ = { 0.0f, 1.0f, 0.0f };												//上方向
		rot_ = { MyMath::PI_OVER_SIX, 0.0f, 0.0f };						//カメラ角度

		dir_ = { 0.0f,0.0f,1.0f };

		distanceToPlayer_ = CAMERA::POS_Z_DISTANCE;

		//カメラ位置設定
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

	}

	//カメラ行動処理関数
	void Camera::Step(const Vector3D& playerPos)
	{
		//カメラの対象物
		target_ = playerPos;

		if (Input::IsKeyKeep(GAME_INPUT::TURBO))
		{
			//カメラが離れられる最大の距離にする
			distanceToPlayer_ = CAMERA::MAX_DISTANCE;

		}
		else
		{
			//プレイヤーの位置からカメラの位置までのベクトル作成
			dir_ = playerPos - pos_;

			//ベクトルの長さ取得
			distanceToPlayer_ = dir_.L2Norm();


			//カメラがこれ以上近づけない距離よりも近い場合
			if (distanceToPlayer_ - CAMERA::SPEED <= CAMERA::MIN_DISTANCE)
			{
				// カメラが近づける距離まで遠ざける
				distanceToPlayer_ = CAMERA::MIN_DISTANCE;

			}
			//カメラがこれ以上離れられない距離を超えた場合
			else if (distanceToPlayer_ >= CAMERA::MAX_DISTANCE)
			{
				//カメラが離れられる最大の距離にする
				distanceToPlayer_ = CAMERA::MAX_DISTANCE;
			}
			else
			{
				//どれにも当てはまらない場合追いかける
				distanceToPlayer_ -= CAMERA::SPEED;
			}
		}

		//自分から見て下方向に回転
		if (InputKeyBoard::IsKeyDown(KEY::UP))
		{
			rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;

			// rot_の上下の角度θの定義域は　0 <= θ <= (π/2) - π/100
			if (rot_.x < 0.0f)
			{
				rot_.x = 0.0f;
			}
		}

		//自分から見て上方向に回転
		if (InputKeyBoard::IsKeyDown(KEY::DOWN))
		{
			rot_.x += CAMERA::ROT_UP_DOWN_SPEED;

			// rot_の上下の角度θの定義域は (-π/2) + π/100 <= θ <= (π/2) - π/100
			if (rot_.x > MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x = MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
			}
		}

		//自分から見て右方向に回転
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_の左右の角度θの定義域は -π < θ <= π
			if (rot_.y < -MyMath::PI)
			{
				rot_.y = MyMath::PI;
			}

		}

		//自分から見て左方向に回転
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_の左右の角度θの定義域は -π <= θ < π
			if (rot_.y > MyMath::PI)
			{
				rot_.y = -MyMath::PI;
			}

		}

		//ゲームパッドのRスティック取得
		const Vector3D GamePadRStick = InputGamePad::GetRStickVector();

		if (MyMath::Abs(GamePadRStick.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(GamePadRStick.y) > Common::KINDA_SMALL_NUMBER)
		{
			rot_ += GamePadRStick * CAMERA::GAMEPAD_ROT_COEFFICIENT;
		}
		
		//マウス視点操作
		const Vector3D MouseMoveValue(InputMouse::GetMoveValueVertical(), InputMouse::GetMoveValueHorizontal(), 0.0f);

		if (MyMath::Abs(MouseMoveValue.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(MouseMoveValue.y) > Common::KINDA_SMALL_NUMBER)
		{
			rot_ += MouseMoveValue * CAMERA::MOUSE_SENSITIVITY;
		}


		//rot_.x < 0
		if (rot_.x < 0.0f)
		{
			rot_.x = 0.0f;
		}

		//rot_.x > π/2
		if (rot_.x >= MyMath::HALF_PI)
		{
			rot_.x = MyMath::HALF_PI - MyMath::INVERSE_TWO_PI;
		}

		//rot_.y < -π/2
		if (rot_.y < -MyMath::PI)
		{
			rot_.y = MyMath::PI;
		}

		//rot_.y > π/2
		if (rot_.y > MyMath::PI)
		{
			rot_.y = -MyMath::PI;
		}
	}

	//カメラ更新関数
	void Camera::UpDate(void)
	{
		//行列によるカメラ位置計算
		Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
			* Matrix3D::GetYawMatrix(rot_.y)
			* Matrix3D::GetPitchMatrix(rot_.x)
			* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - distanceToPlayer_);

		pos_ = RetCameraMat * target_;

		//カメラ向いている方向計算
		dir_ = target_ - pos_;

		//カメラ位置設定
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
	}
}
