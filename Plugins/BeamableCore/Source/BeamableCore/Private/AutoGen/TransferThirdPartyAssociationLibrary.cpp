
#include "BeamableCore/Public/AutoGen/TransferThirdPartyAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTransferThirdPartyAssociationLibrary::TransferThirdPartyAssociationToJsonString(const UTransferThirdPartyAssociation* Serializable, const bool Pretty)
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

UTransferThirdPartyAssociation* UTransferThirdPartyAssociationLibrary::Make(int64 FromAccountId, UThirdPartyAssociation* ThirdParty, UObject* Outer)
{
	auto Serializable = NewObject<UTransferThirdPartyAssociation>(Outer);
	Serializable->FromAccountId = FromAccountId;
	Serializable->ThirdParty = ThirdParty;
	
	return Serializable;
}

void UTransferThirdPartyAssociationLibrary::Break(const UTransferThirdPartyAssociation* Serializable, int64& FromAccountId, UThirdPartyAssociation*& ThirdParty)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		FromAccountId = Serializable->FromAccountId;
		ThirdParty = Serializable->ThirdParty;
	}
		
}

