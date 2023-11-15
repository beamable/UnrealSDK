
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/RoleChangeRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectGroupsPutRoleRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsPutRoleRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URoleChangeRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectGroupsPutRoleRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Groups", DisplayName="Beam - Make ObjectGroupsPutRole",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectGroupsPutRoleRequest* Make(int64 _ObjectId, int64 _GamerTag, FString _Role, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleSuccess, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleError, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsPutRoleComplete, FBeamRequestContext, Context, UObjectGroupsPutRoleRequest*, Request);

using FObjectGroupsPutRoleFullResponse = FBeamFullResponse<UObjectGroupsPutRoleRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsPutRoleFullResponse, FObjectGroupsPutRoleFullResponse);
