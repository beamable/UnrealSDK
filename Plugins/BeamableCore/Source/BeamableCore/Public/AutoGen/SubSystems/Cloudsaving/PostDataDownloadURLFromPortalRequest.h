
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ObjectRequests.h"
#include "AutoGen/URLSResponse.h"

#include "PostDataDownloadURLFromPortalRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostDataDownloadURLFromPortalRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UObjectRequests* Body;

	// Beam Base Request Declaration
	UPostDataDownloadURLFromPortalRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Request,_PlayerId,Outer"))
	static UPostDataDownloadURLFromPortalRequest* MakePostDataDownloadURLFromPortalRequest(FOptionalArrayOfObjectRequestBody _Request, FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLFromPortalSuccess, FBeamRequestContext, Context, UPostDataDownloadURLFromPortalRequest*, Request, UURLSResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostDataDownloadURLFromPortalError, FBeamRequestContext, Context, UPostDataDownloadURLFromPortalRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostDataDownloadURLFromPortalComplete, FBeamRequestContext, Context, UPostDataDownloadURLFromPortalRequest*, Request);

using FPostDataDownloadURLFromPortalFullResponse = FBeamFullResponse<UPostDataDownloadURLFromPortalRequest*, UURLSResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostDataDownloadURLFromPortalFullResponse, FPostDataDownloadURLFromPortalFullResponse);
