
#include "BeamableCore/Public/AutoGen/NewCustomerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNewCustomerResponseLibrary::NewCustomerResponseToJsonString(const UNewCustomerResponse* Serializable, const bool Pretty)
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

UNewCustomerResponse* UNewCustomerResponseLibrary::Make(bool bActivationPending, FString Name, FString ProjectName, FBeamCid Cid, FBeamPid Pid, UTokenResponse* Token, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UNewCustomerResponse>(Outer);
	Serializable->bActivationPending = bActivationPending;
	Serializable->Name = Name;
	Serializable->ProjectName = ProjectName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->Token = Token;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UNewCustomerResponseLibrary::Break(const UNewCustomerResponse* Serializable, bool& bActivationPending, FString& Name, FString& ProjectName, FBeamCid& Cid, FBeamPid& Pid, UTokenResponse*& Token, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bActivationPending = Serializable->bActivationPending;
		Name = Serializable->Name;
		ProjectName = Serializable->ProjectName;
		Cid = Serializable->Cid;
		Pid = Serializable->Pid;
		Token = Serializable->Token;
		Alias = Serializable->Alias;
	}
		
}

