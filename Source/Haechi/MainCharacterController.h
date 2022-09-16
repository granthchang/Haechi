// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class HAECHI_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AMainCharacterController();


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DealtTime) override;

};
