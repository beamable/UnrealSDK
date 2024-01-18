
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookUpdateRequest.h"

void UPostFacebookUpdateRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostFacebookUpdateRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/payments/facebook/update");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostFacebookUpdateRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostFacebookUpdateRequest* UPostFacebookUpdateRequest::Make(FString _Object, TArray<UFacebookUpdatedEntry*> _Entry, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostFacebookUpdateRequest* Req = NewObject<UPostFacebookUpdateRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UFacebookPaymentUpdateRequestBody>(Req);
	Req->Body->Object = _Object;
	Req->Body->Entry = _Entry;
	

	return Req;
}
