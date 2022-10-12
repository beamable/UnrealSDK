
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/PlayerBasicCloudDataRequestBody.h"
#include "AutoGen/Manifest.h"

#include "PutDataMoveFromPortalRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDataMoveFromPortalRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPlayerBasicCloudDataRequestBody* Body;

	// Beam Base Request Declaration
	UPutDataMoveFromPortalRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,Outer"))
	static UPutDataMoveFromPortalRequest* MakePutDataMoveFromPortalRequest(FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveFromPortalSuccess, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request, UManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveFromPortalError, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataMoveFromPortalComplete, FBeamRequestContext, Context, UPutDataMoveFromPortalRequest*, Request);

using FPutDataMoveFromPortalFullResponse = FBeamFullResponse<UPutDataMoveFromPortalRequest*, UManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataMoveFromPortalFullResponse, FPutDataMoveFromPortalFullResponse);
