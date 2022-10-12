
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/GetGroupStatusResponse.h"

#include "GetMeGroupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMeGroupRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FOptionalString ContentId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetMeGroupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_ContentId,Outer"))
	static UGetMeGroupRequest* MakeGetMeGroupRequest(FOptionalString _ContentId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMeGroupSuccess, FBeamRequestContext, Context, UGetMeGroupRequest*, Request, UGetGroupStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMeGroupError, FBeamRequestContext, Context, UGetMeGroupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMeGroupComplete, FBeamRequestContext, Context, UGetMeGroupRequest*, Request);

using FGetMeGroupFullResponse = FBeamFullResponse<UGetMeGroupRequest*, UGetGroupStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetMeGroupFullResponse, FGetMeGroupFullResponse);