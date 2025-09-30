
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicNewCustomerResponseLibrary::RealmsBasicNewCustomerResponseToJsonString(const URealmsBasicNewCustomerResponse* Serializable, const bool Pretty)
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

URealmsBasicNewCustomerResponse* URealmsBasicNewCustomerResponseLibrary::Make(bool bActivationPending, FString Name, FString ProjectName, FBeamCid Cid, FBeamPid Pid, UTokenResponse* Token, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicNewCustomerResponse>(Outer);
	Serializable->bActivationPending = bActivationPending;
	Serializable->Name = Name;
	Serializable->ProjectName = ProjectName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->Token = Token;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void URealmsBasicNewCustomerResponseLibrary::Break(const URealmsBasicNewCustomerResponse* Serializable, bool& bActivationPending, FString& Name, FString& ProjectName, FBeamCid& Cid, FBeamPid& Pid, UTokenResponse*& Token, FOptionalString& Alias)
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

