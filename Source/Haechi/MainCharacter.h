// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"


// Movement Status
UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Idle UMETA(DisplayName = "Normal"),
	EMS_Walk UMETA(DisplayName = "Walk"),
	EMS_Running UMETA(DisplayName = "Running"),

	EMS_MAX UMETA(DisplayName = "DefaultMax")
};





UCLASS()
class HAECHI_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Static MEsh for testing, replace with real skeletal mesh later
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* TestMesh;

	// Camera and SpringArm Component
	UPROPERTY(EditAnywhere, Category = "Component")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USpringArmComponent* CameraBoom;

	//Camera Rotation Rate

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	float BaseTurnRate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Value);

	void MoveForward(float Value);

	void TurnRate(float Rate);

	void LookUpRate(float Rate);

	void Crouching();

	void StopCrouching();

	void Sprinting();

	void StopSprinting();
};
