
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ObjectRequests.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#include "PostDataDownloadURLRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataDownloadURLRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UObjectRequests* Body = {};

	// Beam Base Request Declaration
	UPostDataDownloadURLRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PostDataDownloadURL",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_Request,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostDataDownloadURLRequest* Make(FOptionalInt64 _PlayerId, FOptionalArrayOfObjectRequestBody _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLSuccess, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request, UURLSResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLError, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataDownloadURLComplete, FBeamRequestContext, Context, UPostDataDownloadURLRequest*, Request);

using FPostDataDownloadURLFullResponse = FBeamFullResponse<UPostDataDownloadURLRequest*, UURLSResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDataDownloadURLFullResponse, FPostDataDownloadURLFullResponse);
