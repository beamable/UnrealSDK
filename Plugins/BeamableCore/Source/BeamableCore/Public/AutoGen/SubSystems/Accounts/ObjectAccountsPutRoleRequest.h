
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/UpdateRole.h"
#include "AutoGen/EmptyResponse.h"

#include "ObjectAccountsPutRoleRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAccountsPutRoleRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UUpdateRole* Body;

	// Beam Base Request Declaration
	UObjectAccountsPutRoleRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Cid,_Realm,_Role,Outer"))
	static UObjectAccountsPutRoleRequest* MakeObjectAccountsPutRoleRequest(int64 _ObjectId, FOptionalString _Cid, FOptionalString _Realm, FOptionalString _Role, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAccountsPutRoleSuccess, FBeamRequestContext, Context, UObjectAccountsPutRoleRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAccountsPutRoleError, FBeamRequestContext, Context, UObjectAccountsPutRoleRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAccountsPutRoleComplete, FBeamRequestContext, Context, UObjectAccountsPutRoleRequest*, Request);

using FObjectAccountsPutRoleFullResponse = FBeamFullResponse<UObjectAccountsPutRoleRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAccountsPutRoleFullResponse, FObjectAccountsPutRoleFullResponse);
