
#include "BeamableCore/Public/AutoGen/RealmsBasicAccountLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicAccountLibrary::RealmsBasicAccountToJsonString(const URealmsBasicAccount* Serializable, const bool Pretty)
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

URealmsBasicAccount* URealmsBasicAccountLibrary::Make(FString User, FString Password, TArray<FString> Projects, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicAccount>(Outer);
	Serializable->User = User;
	Serializable->Password = Password;
	Serializable->Projects = Projects;
	Serializable->Created = Created;
	
	return Serializable;
}

void URealmsBasicAccountLibrary::Break(const URealmsBasicAccount* Serializable, FString& User, FString& Password, TArray<FString>& Projects, FOptionalInt64& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		User = Serializable->User;
		Password = Serializable->Password;
		Projects = Serializable->Projects;
		Created = Serializable->Created;
	}
		
}

