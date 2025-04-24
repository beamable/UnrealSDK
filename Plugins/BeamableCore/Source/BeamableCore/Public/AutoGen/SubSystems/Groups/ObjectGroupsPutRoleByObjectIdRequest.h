
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RoleChangeRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectGroupsPutRoleByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsPutRoleByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectGroupsPutRoleByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make ObjectGroupsPutRoleByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectGroupsPutRoleByObjectIdRequest* Make(int64 _ObjectId, int64 _GamerTag, FString _Role, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleByObjectIdSuccess, FBeamRequestContext, Context, UObjectGroupsPutRoleByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPutRoleByObjectIdError, FBeamRequestContext, Context, UObjectGroupsPutRoleByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsPutRoleByObjectIdComplete, FBeamRequestContext, Context, UObjectGroupsPutRoleByObjectIdRequest*, Request);

using FObjectGroupsPutRoleByObjectIdFullResponse = FBeamFullResponse<UObjectGroupsPutRoleByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsPutRoleByObjectIdFullResponse, FObjectGroupsPutRoleByObjectIdFullResponse);
