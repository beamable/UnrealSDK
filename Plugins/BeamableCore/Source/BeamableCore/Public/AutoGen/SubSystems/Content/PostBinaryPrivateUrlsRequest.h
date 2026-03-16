
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsRequestBody.h"
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsResponse.h"

#include "PostBinaryPrivateUrlsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostBinaryPrivateUrlsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetBinaryDownloadUrlsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostBinaryPrivateUrlsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PostBinaryPrivateUrls",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ExpirationSeconds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostBinaryPrivateUrlsRequest* Make(TArray<UGetContentRequestBody*> _Requests, FOptionalInt64 _ExpirationSeconds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostBinaryPrivateUrlsSuccess, FBeamRequestContext, Context, UPostBinaryPrivateUrlsRequest*, Request, UGetBinaryDownloadUrlsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostBinaryPrivateUrlsError, FBeamRequestContext, Context, UPostBinaryPrivateUrlsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostBinaryPrivateUrlsComplete, FBeamRequestContext, Context, UPostBinaryPrivateUrlsRequest*, Request);

using FPostBinaryPrivateUrlsFullResponse = FBeamFullResponse<UPostBinaryPrivateUrlsRequest*, UGetBinaryDownloadUrlsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostBinaryPrivateUrlsFullResponse, FPostBinaryPrivateUrlsFullResponse);
