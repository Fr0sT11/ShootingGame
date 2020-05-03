// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"
#include "SGameMode.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
    DefaultHealth = 100; 
    bIsDead = false;
    SetIsReplicatedByDefault(true);
}

float USHealthComponent::GetHealth()
{
    return Health;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    // Only hook if we are server
    if(GetOwnerRole() == ROLE_Authority)
    {
        AActor* MyOwner = GetOwner();
        if(MyOwner)
        {
            MyOwner->OnTakeAnyDamage.AddDynamic(this,&USHealthComponent::HandleTakeAnyDamage);
        }
    }
    
    Health = DefaultHealth;
}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor,float Damage,const class UDamageType* DamageType,class AController* InstigatedBy,AActor* DamageCauser)
{
    if(Damage <= 0.0f || bIsDead)
    {
        return;
    }

    // Update Health Clamp
    Health = FMath::Clamp(Health - Damage,0.0f,DefaultHealth);

    UE_LOG(LogTemp,Log,TEXT("Health Changed: %s"),*FString::SanitizeFloat(Health));

    bIsDead = Health <= 0.0f;

    OnHealthChanged.Broadcast(this,Health,Damage,DamageType,InstigatedBy,DamageCauser);
    if (Health <= 0.0f)
    {
        ASGameMode* GM = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());
        if (GM)
        {
            GM->OnActorKilled.Broadcast(GetOwner(), DamageCauser, InstigatedBy);
        }    
    }
    
}

void USHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(USHealthComponent,Health);
}