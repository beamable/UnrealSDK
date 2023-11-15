
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/GetDataMetadataRequest.h"

void UGetDataMetadataRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetDataMetadataRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/cloudsaving/data/metadata");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Request.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		bIsFirstQueryParam = false;
	}

	if(PlayerId.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("playerId"), *FString::FromInt(PlayerId.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetDataMetadataRequest::BuildBody(FString& BodyString) const
{
	
}

UGetDataMetadataRequest* UGetDataMetadataRequest::Make(FOptionalArrayOfObjectRequestBody _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetDataMetadataRequest* Req = NewObject<UGetDataMetadataRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Request = _Request;
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
