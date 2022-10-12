
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AddAccountRequestBody.h"
#include "AutoGen/AccountPortalView.h"

#include "PostAdminAdminUserRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostAdminAdminUserRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAddAccountRequestBody* Body;

	// Beam Base Request Declaration
	UPostAdminAdminUserRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Role,Outer"))
	static UPostAdminAdminUserRequest* MakePostAdminAdminUserRequest(FString _Email, FOptionalString _Role, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAdminAdminUserSuccess, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request, UAccountPortalView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAdminAdminUserError, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostAdminAdminUserComplete, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request);

using FPostAdminAdminUserFullResponse = FBeamFullResponse<UPostAdminAdminUserRequest*, UAccountPortalView*>;
DECLARE_DELEGATE_OneParam(FOnPostAdminAdminUserFullResponse, FPostAdminAdminUserFullResponse);
