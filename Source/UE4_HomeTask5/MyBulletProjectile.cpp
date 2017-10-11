// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBulletProjectile.h"

// Sets default values
AMyBulletProjectile::AMyBulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5);
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyBulletProjectile::OnHit);

	BulletMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	BulletMeshCmp->SetSimulatePhysics(false);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshSphere(TEXT("StaticMesh'/Game/Weapon/Shape_Sphere.Shape_Sphere'"));
	if (MeshSphere.Object) {
		BulletMeshCmp->SetStaticMesh(MeshSphere.Object);
	}

	SetMeshScale(MeshScale);
	(Cast<USceneComponent>(BulletMeshCmp))->SetupAttachment(CollisionComp);
	RootComponent = CollisionComp;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->ProjectileGravityScale = .1f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3;
}

void AMyBulletProjectile::SetGravity(float gravity) {
	ProjectileMovement->ProjectileGravityScale = gravity;
}

void AMyBulletProjectile::SetMeshScale(float Scale) {
	(Cast<USceneComponent>(BulletMeshCmp))->SetWorldScale3D(FVector::OneVector * Scale);
}

// Called when the game starts or when spawned
void AMyBulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBulletProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}
