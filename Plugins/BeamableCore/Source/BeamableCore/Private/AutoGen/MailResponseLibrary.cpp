
#include "BeamableCore/Public/AutoGen/MailResponseLibrary.h"

#include "CoreMinimal.h"


FString UMailResponseLibrary::MailResponseToJsonString(const UMailResponse* Serializable, const bool Pretty)
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

UMailResponse* UMailResponseLibrary::Make(FOptionalMessage Result, UObject* Outer)
{
	auto Serializable = NewObject<UMailResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UMailResponseLibrary::Break(const UMailResponse* Serializable, FOptionalMessage& Result)
{
	Result = Serializable->Result;
		
}

