
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ObjectRequests.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteDataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteDataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UObjectRequests* Body;

	// Beam Base Request Declaration
	UDeleteDataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Request,_PlayerId,Outer"))
	static UDeleteDataRequest* MakeDeleteDataRequest(FOptionalArrayOfObjectRequestBody _Request, FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteDataSuccess, FBeamRequestContext, Context, UDeleteDataRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteDataError, FBeamRequestContext, Context, UDeleteDataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteDataComplete, FBeamRequestContext, Context, UDeleteDataRequest*, Request);

using FDeleteDataFullResponse = FBeamFullResponse<UDeleteDataRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteDataFullResponse, FDeleteDataFullResponse);
