
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/DeleteRoleRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteRoleRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRoleRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteRoleRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteRoleRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteRole",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Realm,_Role,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteRoleRequest* Make(FBeamAccountId _ObjectId, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoleSuccess, FBeamRequestContext, Context, UDeleteRoleRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoleError, FBeamRequestContext, Context, UDeleteRoleRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteRoleComplete, FBeamRequestContext, Context, UDeleteRoleRequest*, Request);

using FDeleteRoleFullResponse = FBeamFullResponse<UDeleteRoleRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteRoleFullResponse, FDeleteRoleFullResponse);
