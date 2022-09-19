// Heachi Team EAE

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"



// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up TestMesh
	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));
	TestMesh->SetupAttachment(RootComponent);

	//Setting Up Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(TestMesh);
	CameraBoom->TargetArmLength = 500.f;	//Camera Distance
	CameraBoom->bUsePawnControlRotation = true;		//Allow player to control camera rotation

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;		//Camera do not rotate with the arm

	
	//Configure movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	BaseTurnRate = 50.f;

	//Jumping
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetCharacterMovement()->MaxWalkSpeed = 600.f;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Jumping Keybind
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Crouching Keybind
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::Crouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::StopCrouching);

	//Movement Input
	PlayerInputComponent->BindAxis("MoveR/L", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveF/B", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookR/L", this, &AMainCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookU/D", this, &AMainCharacter::LookUpRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprinting);
}

void AMainCharacter::MoveRight(float Value)
{
	//Find forward direction
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);

}

void AMainCharacter::MoveForward(float Value)
{
	//Find forward direction
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);

}
void AMainCharacter::TurnRate(float Rate)
{
	AddControllerYawInput(Rate* BaseTurnRate* GetWorld()->GetDeltaSeconds());
}
void AMainCharacter::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate* BaseTurnRate* GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::Crouching()
{
	TestMesh->SetRelativeScale3D(FVector(1, 0.75, 1));
	UE_LOG(LogTemp, Warning, TEXT("Crouching"));
	Crouch();
}

void AMainCharacter::StopCrouching()
{
	TestMesh->SetRelativeScale3D(FVector(1, 1, 1));
	UE_LOG(LogTemp, Warning, TEXT("EndCrouch"));
	UnCrouch();
}

void AMainCharacter::Sprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	UE_LOG(LogTemp, Warning, TEXT("Sprinting"));
}

void AMainCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	UE_LOG(LogTemp, Warning, TEXT("EndSprint"));
}