
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPartyRequest.h"

void UPutPartyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPartyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/parties/{id}");
	Route = Route.Replace(TEXT("{id}"), *Id.ToString(EGuidFormats::DigitsWithHyphensLower));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPartyRequest::BuildBody(FString& BodyString) const
{
	
}

UPutPartyRequest* UPutPartyRequest::Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPartyRequest* Req = NewObject<UPutPartyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Id = _Id;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
