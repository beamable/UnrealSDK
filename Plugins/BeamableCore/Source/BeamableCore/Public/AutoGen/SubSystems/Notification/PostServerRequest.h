
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ServerEvent.h"
#include "AutoGen/CommonResponse.h"

#include "PostServerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UServerEvent* Body;

	// Beam Base Request Declaration
	UPostServerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Payload,Outer"))
	static UPostServerRequest* MakePostServerRequest(FString _Event, FOptionalString _Payload, bool _bToAll, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServerSuccess, FBeamRequestContext, Context, UPostServerRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServerError, FBeamRequestContext, Context, UPostServerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServerComplete, FBeamRequestContext, Context, UPostServerRequest*, Request);

using FPostServerFullResponse = FBeamFullResponse<UPostServerRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostServerFullResponse, FPostServerFullResponse);
