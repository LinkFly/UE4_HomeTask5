// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "MyBulletProjectile.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "MyCharacter.generated.h"

UCLASS()
class UE4_HOMETASK5_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraFollow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AMyBulletProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TurnRate = 45;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LookUpRate = 45;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bWeaponVisible = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector GunOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BulletScale = .15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BulletGravity = .025f;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector Velocity;
	const FName GunAmmoSocket = FName(TEXT("AmmoSocket"));
	const FName ForGunSocket = FName(TEXT("thumb_01_r"));
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void Lookup(float AxisValue);
	void ShootBullet();
	void StartFire();
	void EndFire();
	void SwitchWeapon();
};
