
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/UpdateRole.h"
#include "AutoGen/EmptyResponse.h"

#include "PutAdminScopeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminScopeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateRole* Body;

	// Beam Base Request Declaration
	UPutAdminScopeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make PutAdminScope",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Cid,_Realm,_Role,Outer"))
	static UPutAdminScopeRequest* Make(int64 _ObjectId, FOptionalString _Cid, FOptionalString _Realm, FOptionalString _Role, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminScopeSuccess, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminScopeError, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminScopeComplete, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request);

using FPutAdminScopeFullResponse = FBeamFullResponse<UPutAdminScopeRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminScopeFullResponse, FPutAdminScopeFullResponse);
