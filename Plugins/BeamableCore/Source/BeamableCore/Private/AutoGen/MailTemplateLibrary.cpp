
#include "BeamableCore/Public/AutoGen/MailTemplateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailTemplateLibrary::MailTemplateToJsonString(const UMailTemplate* Serializable, const bool Pretty)
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

UMailTemplate* UMailTemplateLibrary::Make(FString Subject, FString Body, UObject* Outer)
{
	auto Serializable = NewObject<UMailTemplate>(Outer);
	Serializable->Subject = Subject;
	Serializable->Body = Body;
	
	return Serializable;
}

void UMailTemplateLibrary::Break(const UMailTemplate* Serializable, FString& Subject, FString& Body)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Subject = Serializable->Subject;
		Body = Serializable->Body;
	}
		
}

