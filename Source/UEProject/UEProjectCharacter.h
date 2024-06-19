// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <UEProject/MeleeHitRange.h>
#include "Components/SphereComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "MyWeaponPickUp.h"
#include "HealthPickUp.h"

#include "UEProjectCharacter.generated.h"

UCLASS(config=Game)
class AUEProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AUEProjectCharacter();

	void BeginPlay();
	void Tick(float DeltaTime);
	void restartAnim();
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	void HandleBombPlace();
	UPROPERTY(EditAnywhere, Category = "Bomb")
		TSubclassOf<class ABomb> BombShape;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gameEFFECT")
		class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gameEFFECT")
		class UAnimMontage* FireAnimation;
	class UAnimInstance* AnimInstance;
	class UWorld* world;

	FRotator SpawnRotation;
	FVector SpawnLocation;
	void shoot();
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		float health = 100.f;
		public:
	void DealDamage(float DamageAmount);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 LoadedAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		class UAnimMontage* reloadAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 ammoPool;
	void OnReload();
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		bool NeedReload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombSound")
		class USoundBase* BombSound;
	UPROPERTY(EditAnywhere)
		UParticleSystem* muzzleFlash;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void Attack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationHit")
		AMeleeHitRange* hitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationHit")
		AActor* MeleeAttack;
	/*UPROPERTY(EditAnywhere, Category = "AnimationHit")
		UAnimSequence* Hit;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationHit")
		class USoundBase* hitSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationHit")
		class UAnimMontage* Hit;
	void Interact();
	UPROPERTY(EditAnywhere, Category = "PickUp")
		USphereComponent* collectionRange;

	UPROPERTY(EditAnywhere, Category = "PickUp")
		ASkeletalMeshActor* wielded;
	bool AbleToShoot;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

