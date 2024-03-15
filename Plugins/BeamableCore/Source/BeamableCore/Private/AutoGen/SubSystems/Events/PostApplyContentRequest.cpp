
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PostApplyContentRequest.h"

void UPostApplyContentRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostApplyContentRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/events/applyContent");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostApplyContentRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostApplyContentRequest* UPostApplyContentRequest::Make(UEvent* _Content, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostApplyContentRequest* Req = NewObject<UPostApplyContentRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UEventApplyRequestBody>(Req);
	// Assumes the object is constructed and have the new request take ownership of the memory for it
	Req->Body->Content = _Content;
	Req->Body->Content->Rename(nullptr, Req);
	

	return Req;
}
