
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetManifestsRequest.h"

void UApiBeamoGetManifestsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetManifestsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/manifests");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Offset.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("offset"), *FString::FromInt(Offset.Val));
		bIsFirstQueryParam = false;
	}

	if(Limit.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("limit"), *FString::FromInt(Limit.Val));
		bIsFirstQueryParam = false;
	}

	if(bArchived.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("archived"), bArchived.Val ? TEXT("true") : TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetManifestsRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetManifestsRequest* UApiBeamoGetManifestsRequest::Make(FOptionalInt32 _Offset, FOptionalInt32 _Limit, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetManifestsRequest* Req = NewObject<UApiBeamoGetManifestsRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Offset = _Offset;
	Req->Limit = _Limit;
	Req->bArchived = _bArchived;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
