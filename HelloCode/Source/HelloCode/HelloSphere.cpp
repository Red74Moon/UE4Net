// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));

	RootComponent = SphereComponent;
	
	//구체 컴포넌트에 속성을 적용한다.
	SphereComponent->InitSphereRadius(220.0f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereVisual->AttachTo(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	ConstructorHelpers::FObjectFinder<UMaterial> SpherMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));

	if (SphereAsset.Succeeded() && SpherMaterial.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		SphereVisual->SetMaterial(0, SpherMaterial.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	}

	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));

	FireParticles->AttachTo(SphereVisual);
	FireParticles->bAutoActivate = true;

	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));

	if (FireVisual.Succeeded())
	{
		FireParticles->SetTemplate(FireVisual.Object);
	}

	// 텍스트 컴포넌트 추가
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	TextRenderComponent->AttachTo(SphereVisual);

	TextRenderComponent->SetRelativeLocation(FVector(100.0f, 100.0f, 110.0f));

	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));

	//델리게이트 바인드
	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);

}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelloSphere::MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello " + OtherActor->GetName() + "!";
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}

