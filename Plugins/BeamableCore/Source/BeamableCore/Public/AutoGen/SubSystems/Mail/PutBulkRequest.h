
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BulkUpdateMailObjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "PutBulkRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutBulkRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBulkUpdateMailObjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutBulkRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make PutBulk",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutBulkRequest* Make(int64 _ObjectId, TArray<UMyMailUpdate*> _UpdateMailRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutBulkSuccess, FBeamRequestContext, Context, UPutBulkRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutBulkError, FBeamRequestContext, Context, UPutBulkRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutBulkComplete, FBeamRequestContext, Context, UPutBulkRequest*, Request);

using FPutBulkFullResponse = FBeamFullResponse<UPutBulkRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutBulkFullResponse, FPutBulkFullResponse);
