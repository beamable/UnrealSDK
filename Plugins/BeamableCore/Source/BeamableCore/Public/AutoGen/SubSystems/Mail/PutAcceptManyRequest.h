
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AcceptMultipleAttachments.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "PutAcceptManyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAcceptManyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAcceptMultipleAttachments* Body = {};

	// Beam Base Request Declaration
	UPutAcceptManyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make PutAcceptMany",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAcceptManyRequest* Make(int64 _ObjectId, TArray<int64> _MailIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAcceptManySuccess, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAcceptManyError, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAcceptManyComplete, FBeamRequestContext, Context, UPutAcceptManyRequest*, Request);

using FPutAcceptManyFullResponse = FBeamFullResponse<UPutAcceptManyRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAcceptManyFullResponse, FPutAcceptManyFullResponse);
