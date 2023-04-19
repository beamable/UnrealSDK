
#include "BeamableCore/Public/AutoGen/NewCustomerResponseLibrary.h"

#include "CoreMinimal.h"


FString UNewCustomerResponseLibrary::NewCustomerResponseToJsonString(const UNewCustomerResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UNewCustomerResponse* UNewCustomerResponseLibrary::Make(FString Name, FString ProjectName, FBeamCid Cid, FBeamPid Pid, UTokenResponse* Token, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UNewCustomerResponse>(Outer);
	Serializable->Name = Name;
	Serializable->ProjectName = ProjectName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->Token = Token;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UNewCustomerResponseLibrary::Break(const UNewCustomerResponse* Serializable, FString& Name, FString& ProjectName, FBeamCid& Cid, FBeamPid& Pid, UTokenResponse*& Token, FOptionalString& Alias)
{
	Name = Serializable->Name;
	ProjectName = Serializable->ProjectName;
	Cid = Serializable->Cid;
	Pid = Serializable->Pid;
	Token = Serializable->Token;
	Alias = Serializable->Alias;
		
}

