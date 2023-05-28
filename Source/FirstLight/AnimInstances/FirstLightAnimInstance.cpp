// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightAnimInstance.h"

#include "FirstLight/Core/FirstLightCharacter.h"
#include "FirstLightGameTypes.h"
#include "Animation/AnimationAsset.h"
#include "Animation/BlendSpace.h"
#include "FirstLight/DataAssets/CharacterAnimDataAsset.h"

UBlendSpace* UFirstLightAnimInstance::GetLocomotionBlendSpace() const
{
	if(const AFirstLightCharacter* FirstLightCharacter = Cast<AFirstLightCharacter>(GetOwningActor()))
	{
		if(const FCharacterData Data = FirstLightCharacter->GetCharacterData(); Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.MovementBlendSpace;
		}
	}
	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.MovementBlendSpace : nullptr;
}

UAnimSequenceBase* UFirstLightAnimInstance::GetIdleAnimation() const
{
	if(const AFirstLightCharacter* FirstLightCharacter = Cast<AFirstLightCharacter>(GetOwningActor()))
	{
		FCharacterData Data = FirstLightCharacter->GetCharacterData();

		if(Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset;
		}
	}
	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset : nullptr;
}
