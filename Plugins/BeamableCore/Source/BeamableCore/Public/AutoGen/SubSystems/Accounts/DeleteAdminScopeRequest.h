
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/DeleteRoleRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteAdminScopeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAdminScopeRequest : public UObject, public IBeamBaseRequestInterface
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
	UDeleteAdminScopeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteAdminScopeRequest* MakeDeleteAdminScopeRequest(int64 _ObjectId, FString _Realm, FString _Role, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminScopeSuccess, FBeamRequestContext, Context, UDeleteAdminScopeRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminScopeError, FBeamRequestContext, Context, UDeleteAdminScopeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAdminScopeComplete, FBeamRequestContext, Context, UDeleteAdminScopeRequest*, Request);

using FDeleteAdminScopeFullResponse = FBeamFullResponse<UDeleteAdminScopeRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAdminScopeFullResponse, FDeleteAdminScopeFullResponse);
