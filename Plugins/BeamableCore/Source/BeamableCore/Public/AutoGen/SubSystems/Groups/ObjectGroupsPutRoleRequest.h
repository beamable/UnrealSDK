
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/RoleChangeRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "ObjectGroupsPutRoleRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsPutRoleRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URoleChangeRequestBody* Body;

	// Beam Base Request Declaration
	UObjectGroupsPutRoleRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_SubGroup,Outer"))
	static UObjectGroupsPutRoleRequest* MakeObjectGroupsPutRoleRequest(int64 _ObjectId, int64 _GamerTag, FString _Role, FOptionalInt64 _SubGroup, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleSuccess, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleError, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsPutRoleComplete, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request);

using FObjectGroupsPutRoleFullResponse = FBeamFullResponse<UObjectGroupsPutRoleRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsPutRoleFullResponse, FObjectGroupsPutRoleFullResponse);
