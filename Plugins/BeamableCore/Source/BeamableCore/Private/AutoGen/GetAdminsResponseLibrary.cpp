
#include "BeamableCore/Public/AutoGen/GetAdminsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetAdminsResponseLibrary::GetAdminsResponseToJsonString(const UGetAdminsResponse* Serializable, const bool Pretty)
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

UGetAdminsResponse* UGetAdminsResponseLibrary::Make(TArray<UAccountPortalView*> Accounts, UObject* Outer)
{
	auto Serializable = NewObject<UGetAdminsResponse>(Outer);
	Serializable->Accounts = Accounts;
	
	return Serializable;
}

void UGetAdminsResponseLibrary::Break(const UGetAdminsResponse* Serializable, TArray<UAccountPortalView*>& Accounts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Accounts = Serializable->Accounts;
	}
		
}

