
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/DeleteRoleRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteRoleRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRoleRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UDeleteRoleRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteRoleRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteRoleRequest* MakeDeleteRoleRequest(int64 _ObjectId, FString _Realm, FString _Role, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoleSuccess, FBeamRequestContext, Context, UDeleteRoleRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoleError, FBeamRequestContext, Context, UDeleteRoleRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteRoleComplete, FBeamRequestContext, Context, UDeleteRoleRequest*, Request);

using FDeleteRoleFullResponse = FBeamFullResponse<UDeleteRoleRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteRoleFullResponse, FDeleteRoleFullResponse);
