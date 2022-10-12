
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/PlayerBasicCloudDataRequestBody.h"
#include "AutoGen/Manifest.h"

#include "PutDataMoveRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDataMoveRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPlayerBasicCloudDataRequestBody* Body;

	// Beam Base Request Declaration
	UPutDataMoveRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,Outer"))
	static UPutDataMoveRequest* MakePutDataMoveRequest(FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveSuccess, FBeamRequestContext, Context, UPutDataMoveRequest*, Request, UManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataMoveError, FBeamRequestContext, Context, UPutDataMoveRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataMoveComplete, FBeamRequestContext, Context, UPutDataMoveRequest*, Request);

using FPutDataMoveFullResponse = FBeamFullResponse<UPutDataMoveRequest*, UManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataMoveFullResponse, FPutDataMoveFullResponse);
