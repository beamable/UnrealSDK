
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorPromoteRealmRequestBodyLibrary::CustomerActorPromoteRealmRequestBodyToJsonString(const UCustomerActorPromoteRealmRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCustomerActorPromoteRealmRequestBody* UCustomerActorPromoteRealmRequestBodyLibrary::Make(FString SourceRealmId, FOptionalArrayOfBeamPromotableType Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorPromoteRealmRequestBody>(Outer);
	Serializable->SourceRealmId = SourceRealmId;
	Serializable->Promotions = Promotions;
	Serializable->ContentManifestIds = ContentManifestIds;
	
	return Serializable;
}

void UCustomerActorPromoteRealmRequestBodyLibrary::Break(const UCustomerActorPromoteRealmRequestBody* Serializable, FString& SourceRealmId, FOptionalArrayOfBeamPromotableType& Promotions, FOptionalArrayOfString& ContentManifestIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmId = Serializable->SourceRealmId;
		Promotions = Serializable->Promotions;
		ContentManifestIds = Serializable->ContentManifestIds;
	}
		
}

