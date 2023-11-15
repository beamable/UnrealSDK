
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AddAccountRequestBody.h"
#include "BeamableCore/Public/AutoGen/AccountPortalView.h"

#include "PostAdminAdminUserRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostAdminAdminUserRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAddAccountRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostAdminAdminUserRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make PostAdminAdminUser",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Role,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostAdminAdminUserRequest* Make(FString _Email, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAdminAdminUserSuccess, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request, UAccountPortalView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAdminAdminUserError, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostAdminAdminUserComplete, FBeamRequestContext, Context, UPostAdminAdminUserRequest*, Request);

using FPostAdminAdminUserFullResponse = FBeamFullResponse<UPostAdminAdminUserRequest*, UAccountPortalView*>;
DECLARE_DELEGATE_OneParam(FOnPostAdminAdminUserFullResponse, FPostAdminAdminUserFullResponse);
