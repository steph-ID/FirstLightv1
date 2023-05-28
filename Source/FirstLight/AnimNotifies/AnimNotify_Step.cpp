// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Step.h"

#include "FirstLight/Core/FirstLightCharacter.h"

void UAnimNotify_Step::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	check(MeshComp);

	AFirstLightCharacter* Character = MeshComp ? Cast<AFirstLightCharacter>(MeshComp->GetOwner()) : nullptr;
	if (Character)
	{
		if (UFootstepsComponent* FootstepsComponent = Character->GetFootstepsComponent())
		{
			FootstepsComponent->HandleFootstep(Foot);
		}
	}
}
